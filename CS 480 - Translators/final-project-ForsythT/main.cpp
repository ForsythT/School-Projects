#include "ast.hpp"
#include "parser.hpp"
#include <iterator>

extern int yylex();

extern ASTBlock* programBlock;
extern std::map<std::string, llvm::Value*> TheSymbolTable;

llvm::LLVMContext TheContext;
llvm::IRBuilder<> TheBuilder(TheContext);
llvm::Module* TheModule;

void generateObjCode(const std::string& filename) {
	std::string targetTriple = llvm::sys::getDefaultTargetTriple();

	llvm::InitializeAllTargetInfos();
	llvm::InitializeAllTargets();
	llvm::InitializeAllTargetMCs();
	llvm::InitializeAllAsmParsers();
	llvm::InitializeAllAsmPrinters();

	std::string error;
	const llvm::Target* target = llvm::TargetRegistry::lookupTarget(targetTriple, error);
	if (!target) {
		std::cerr << error << std::endl;
	} else {
		std::string cpu = "generic";
		std::string features = "";
		llvm::TargetOptions options;
		llvm::TargetMachine* targetMachine = 
			target->createTargetMachine(targetTriple, cpu, features, 
			options, llvm::Optional<llvm::Reloc::Model>());

		TheModule->setDataLayout(targetMachine->createDataLayout());
		TheModule->setTargetTriple(targetTriple);

		std::error_code ec;
		llvm::raw_fd_ostream file(filename, ec, llvm::sys::fs::F_None);
		if (ec) {
			std::cerr << "Could not open output file: " << ec.message() << std::endl;
		} else {
			llvm::TargetMachine::CodeGenFileType type = llvm::TargetMachine::CGFT_ObjectFile;
			llvm::legacy::PassManager pm;
			if (targetMachine->addPassesToEmitFile(pm, file, NULL, type)) {
				std::cerr << "Can't emit object file for target machine" << std::endl;
			} else {
				pm.run(*TheModule);
				file.close();
			}
		}
	}
}

void doOptimizations(llvm::Function* fn) {
	llvm::legacy::FunctionPassManager* fpm = new llvm::legacy::FunctionPassManager(TheModule);

	fpm->add(llvm::createPromoteMemoryToRegisterPass());
	fpm->add(llvm::createReassociatePass());
	fpm->add(llvm::createGVNPass());
	fpm->add(llvm::createCFGSimplificationPass());

	fpm->run(*fn);
}

int main(int argc, char const *argv[]) {
	if (!yylex()) {
		if (programBlock) {
			// Initialize module and compiler main function/entry block
			TheModule = new llvm::Module("Python compiler", TheContext);

			llvm::FunctionType* mainFnType = llvm::FunctionType::get(
				llvm::Type::getFloatTy(TheContext), false
			);

			llvm::Function* mainFn = llvm::Function::Create(mainFnType,
				llvm::GlobalValue::ExternalLinkage, "python_compiler", 
				TheModule);

			llvm::BasicBlock* entryBlock = llvm::BasicBlock::Create(TheContext, "entry", mainFn);
			TheBuilder.SetInsertPoint(entryBlock);

			// Start generating LLVM code from program block
			programBlock->generateLLVMSpec();
			
			llvm::Value* returnSSA = TheBuilder.CreateRet(variableValue("sphere_surf_area"));

			if (argc > 1 && std::string(argv[1]) == "-O") {
				doOptimizations(mainFn);
			}

			llvm::verifyFunction(*mainFn);

			TheModule->print(llvm::outs(), NULL);

			std::string filename = "python_compiler.o";
			generateObjCode(filename);
			
			std::map<std::string, llvm::Value*>::iterator it = TheSymbolTable.begin();
			
			delete TheModule;
		}
	}
  return 0;
}
