#include <iostream>
#include <vector>

/* These need to be declared before parser.hpp can be included, which is included to use the enums. */
class Expr;
class Statement;
class Block;

#include "parser.hpp"

#ifndef EXPR
#define EXPR

class Expr {
	public:
		std::string data;
		Expr *lhs, *rhs;
		Expr(int i, std::string d = "", Expr *l = nullptr, Expr *r = nullptr) {
			switch(i) {
				case IDENTIFIER : data = std::string("Identifier: " + d);
					break;
				case FLOAT : data = std::string("Float: " + d);
					break;
				case INTEGER : data = std::string("Integer: " + d);
					break;
				case BOOLEAN : data = std::string("Boolean: " + d);
					break;
				case NOT : data = std::string("NOT");
					break;
				case PLUS : data = std::string("PLUS");
					break;
				case MINUS : data = std::string("MINUS");
					break;
				case TIMES : data = std::string("TIMES");
					break;
				case DIVIDEDBY : data = std::string("DIVIDEDBY");
					break;
				case EQ : data = std::string("EQ");
					break;
				case NEQ : data = std::string("NEQ");
					break;
				case GT : data = std::string("GT");
					break;
				case GTE : data = std::string("GTE");
					break;
				case LT : data = std::string("LT");
					break;
				case LTE : data = std::string("LTE");
					break;
				case AND : data = std::string("AND");
					break;
				case OR : data = std::string("OR");
					break;
			}
			lhs = l;
			rhs = r;
		}
};

#endif

#ifndef STATEMENT
#define STATEMENT

class Statement {
	public:
		int type;
		std::string data;
		Expr *lhs, *rhs, *condition;
		Block *block, *el;
		Statement *elif;
		Statement(int i, Expr *l = nullptr, Expr *r = nullptr, Expr *c = nullptr, Block *b = nullptr, Block *e = nullptr, Statement *ei = nullptr) {
			switch(i) {
				case ASSIGN : data = std::string("Assignment");
					break;
				case IF : data = std::string("If");
					break;
				case WHILE : data = std::string("While");
					break;
				case BREAK : data = std::string("Break");
					break;
			}
			type = i;
			lhs = l;
			rhs = r;
			condition = c;
			block = b;
			el = e;
			elif = ei;
		}
		bool hasElif() {
			if (elif) {
				return true;
			} else {
				return false;
			}
		}
		bool hasElse() {
			if (el) {
				return true;
			} else {
				return false;
			}
		}
};

#endif

#ifndef BLOCK
#define BLOCK

class Block {
	public:
		std::string data;
		std::vector<Statement*> statements;
		Block() {
			data = std::string("Block");
		}
};

#endif

