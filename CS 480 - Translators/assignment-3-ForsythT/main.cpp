#include <set>
#include "ast.hpp"
#include "parser.hpp"

extern int yylex();
extern Block *target_program_ast;

std::string gv;

void traverseExpr(Expr*, std::string, int);
void traverseStatement(Statement*, std::string);
void traverseBlock(Block*, std::string);

int main() {
	if (!yylex()) {
		std::string name = "n0";
		gv.append("digraph G {\n");
		traverseBlock(target_program_ast, name);
		gv.append("}\n");
		std::cout << gv;
	}
}

void traverseExpr(Expr *expr, std::string str, int type) {
	std::string name = str;
	switch (type) {
		case 0 : name.append("_rhs");
			break;	 
		case 1 : name.append("_lhs");
			break;
		case 2 : name.append("_cond");
			break;
	}
	gv.append("  " + str + " -> " + name + ";\n");
	if (expr->lhs) {
		gv.append("  " + name + " [label=\"" + expr->data + "\"];\n");
		traverseExpr(expr->lhs, name, 1);
		if (expr->rhs) {
			traverseExpr(expr->rhs, name, 0);
		}
	} else if (expr->rhs) {
		gv.append("  " + name + " [label=\"" + expr->data + "\"];\n");
		traverseExpr(expr->rhs, name, 0);
	} else {
		gv.append("  " + name + " [shape=box,label=\"" + expr->data + "\"];\n");	 
	}
}

void traverseStatement(Statement *stmt, std::string str) {	
	std::string name = str;
	gv.append("  " + name + " [label=\"" + stmt->data + "\"];\n");
	switch(stmt->type) {
		case ASSIGN:
			traverseExpr(stmt->lhs, name, 1);
			traverseExpr(stmt->rhs, name, 0);
			break;
		case IF:
			traverseExpr(stmt->condition, name, 2);
			if (stmt->block) {
				name.append("_if");
				gv.append("  " + str + " -> " + name + ";\n");
				traverseBlock(stmt->block, name);
			}
			if (stmt->hasElif()) {
				traverseStatement(stmt->elif, name);
			} else if (stmt->hasElse()) {
				name.replace(name.end()-3, name.end(), "_else");
				gv.append("  " + str + " -> " + name + ";\n");
				traverseBlock(stmt->el, name);
			}
			break;
		case WHILE:
			traverseExpr(stmt->condition, name, 2);
			if (stmt->block) { 
				name.append("_while");
				gv.append("  " + str + " -> " + name + ";\n");
				traverseBlock(stmt->block, name);
			}
			break;
	}
}

void traverseBlock(Block *block, std::string str) {
	int count = 0;
	std::vector<Statement*>::iterator it;
	gv.append("  " + str + " [label=\"" + block->data + "\"];\n");
	for (it = block->statements.begin(); it != block->statements.end(); it++) {
		std::string name = str;
		name.append("_" + std::to_string(count));
		gv.append("  " + str + " -> " + name + ";\n");
		traverseStatement((*it), name);
		count++;
	}
}
