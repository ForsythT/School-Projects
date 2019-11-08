#include "ast.hpp"
#include "parser.hpp"

std::map<std::string, llvm::Value*> TheSymbolTable;

extern llvm::LLVMContext TheContext;
extern llvm::IRBuilder<> TheBuilder;
extern llvm::Module* TheModule;

/*
 * Simple template function to convert a value of any type to a string
 * representation.  The type must have an insertion operator (i.e. operator<<).
 */
template <class T>
std::string toString(const T& val) {
  std::ostringstream out;
  out << val;
  return out.str();
}


llvm::AllocaInst*
generateEntryBlockAlloca(const std::string& name) {
	llvm::Function* currFn = TheBuilder.GetInsertBlock()->getParent();
	llvm::IRBuilder<> tmpBuilder(&currFn->getEntryBlock(), currFn->getEntryBlock().begin());
	return tmpBuilder.CreateAlloca(
		llvm::Type::getFloatTy(TheContext), 0, name.c_str()
	);
}


llvm::Value* variableValue(const std::string& name) {
	llvm::Value* val = TheSymbolTable[name];
	if (!val) {
		std::cerr << "Unknown variable: " << name << std::endl;
		return NULL;
	}
	return TheBuilder.CreateLoad(val, name.c_str());
}


/*
 * Function to generate LLVM spec for the subtree rooted at any node in
 * an AST.
 *
 * @param node An AST node.
 *
 * @return Returns a llvm::Value*.
 */
llvm::Value* generateLLVMSpec(ASTNode* node) {
	return node->generateLLVMSpec();
}

/****************************************************************************
 **
 ** Below is the implementation of generateLLVMSpec() for each class defined in
 ** ast.hpp.  Please see the documentation in ast.hpp for a desription of
 ** this function.
 **
 ****************************************************************************/

llvm::Value* ASTIdentifier::generateLLVMSpec() const {
	return variableValue(*this->name);
}


llvm::Value* ASTFloat::generateLLVMSpec() const {
	return llvm::ConstantFP::get(TheContext, llvm::APFloat(this->value));
}


llvm::Value* ASTInteger::generateLLVMSpec() const {
	return llvm::ConstantFP::get(TheContext, llvm::APFloat((float)this->value));
}


llvm::Value* ASTBoolean::generateLLVMSpec() const {
	return llvm::ConstantFP::get(TheContext, llvm::APFloat((float)this->value));
}


llvm::Value* ASTBinaryOperatorExpression::generateLLVMSpec() const {
	llvm::Value* lhs;
	switch (this->op) {
		case PLUS:
			return TheBuilder.CreateFAdd(this->lhs->generateLLVMSpec(), this->rhs->generateLLVMSpec(), "addtmp");
		case MINUS:
			return TheBuilder.CreateFSub(this->lhs->generateLLVMSpec(), this->rhs->generateLLVMSpec(), "subtmp");
		case TIMES:
			return TheBuilder.CreateFMul(this->lhs->generateLLVMSpec(), this->rhs->generateLLVMSpec(), "multmp");
		case DIVIDEDBY:
			return TheBuilder.CreateFDiv(this->lhs->generateLLVMSpec(), this->rhs->generateLLVMSpec(), "divtmp");
		case EQ:
			lhs = TheBuilder.CreateFCmpUEQ(this->lhs->generateLLVMSpec(), this->rhs->generateLLVMSpec(), "lttmp");
			return TheBuilder.CreateUIToFP(lhs, llvm::Type::getFloatTy(TheContext), "booltmp");
		case NEQ:
			lhs = TheBuilder.CreateFCmpUNE(this->lhs->generateLLVMSpec(), this->rhs->generateLLVMSpec(), "lttmp");
			return TheBuilder.CreateUIToFP(lhs, llvm::Type::getFloatTy(TheContext), "booltmp");
		case GT:
			lhs = TheBuilder.CreateFCmpUGT(this->lhs->generateLLVMSpec(), this->rhs->generateLLVMSpec(), "lttmp");
			return TheBuilder.CreateUIToFP(lhs, llvm::Type::getFloatTy(TheContext), "booltmp");
		case GTE:
			lhs = TheBuilder.CreateFCmpUGE(this->lhs->generateLLVMSpec(), this->rhs->generateLLVMSpec(), "lttmp");
			return TheBuilder.CreateUIToFP(lhs, llvm::Type::getFloatTy(TheContext), "booltmp");
		case LT:
			lhs = TheBuilder.CreateFCmpULT(this->lhs->generateLLVMSpec(), this->rhs->generateLLVMSpec(), "lttmp");
			return TheBuilder.CreateUIToFP(lhs, llvm::Type::getFloatTy(TheContext), "booltmp");
		case LTE:
			lhs = TheBuilder.CreateFCmpULE(this->lhs->generateLLVMSpec(), this->rhs->generateLLVMSpec(), "lttmp");
			return TheBuilder.CreateUIToFP(lhs, llvm::Type::getFloatTy(TheContext), "booltmp");
		default:
			std::cerr << "Invalid operator: " << this->op << std::endl;
			return NULL;
  	}
}


llvm::Value* ASTAssignmentStatement::generateLLVMSpec() const {
	if (!this->rhs) {
		return NULL;
	}

	if (!TheSymbolTable.count(*this->lhs->name)) {
		TheSymbolTable[*this->lhs->name] = generateEntryBlockAlloca(*this->lhs->name);
	}

	return TheBuilder.CreateStore(this->rhs->generateLLVMSpec(), TheSymbolTable[*this->lhs->name]);
}


llvm::Value* ASTBlock::generateLLVMSpec() const {
	for (int i = 0; i < this->statements.size(); i++) {
		this->statements[i]->generateLLVMSpec();
	}	
}


llvm::Value* ASTIfStatement::generateLLVMSpec() const {
}


llvm::Value* ASTWhileStatement::generateLLVMSpec() const {
}


llvm::Value* ASTBreakStatement::generateLLVMSpec() const {
}
