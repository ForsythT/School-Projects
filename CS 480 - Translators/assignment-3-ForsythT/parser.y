%{
#include <set>

#include "ast.hpp"
#include "parser.hpp"

extern int yylex();
void yyerror(YYLTYPE* loc, const char* err);
std::string* translate_boolean_str(std::string* boolean_str);
void insertElse(Statement *elif, Block *el);
void insertElif(Statement *s, Statement *elif, Block *el);

/*
 * Here, target_program_ast is a block that will hold the root node of
 * the target program ast being generated.
 */
Block *target_program_ast;
bool init = false;

%}

/* Enable location tracking. */
%locations

/*
 * All program constructs will be represented as strings, specifically as
 * their corresponding C/C++ translation.
 */
/*%define api.value.type { std::string* }*/
%union {
	std::string *str;
	Expr *expr;
	Statement *stmt;
	Block *blk;
}

/*
 * Because the lexer can generate more than one token at a time (i.e. DEDENT
 * tokens), we'll use a push parser.
 */
%define api.pure full
%define api.push-pull push

/*
 * These are all of the terminals in our grammar, i.e. the syntactic
 * categories that can be recognized by the lexer.
 */
%token <str> IDENTIFIER
%token <str> FLOAT INTEGER BOOLEAN
%token <str> INDENT DEDENT NEWLINE
%token <str> AND BREAK DEF ELIF ELSE FOR IF NOT OR RETURN WHILE
%token <str> ASSIGN PLUS MINUS TIMES DIVIDEDBY
%token <str> EQ NEQ GT GTE LT LTE
%token <str> LPAREN RPAREN COMMA COLON

%type <expr> expression primary_expression negated_expression condition
%type <stmt> statement assign_statement if_statement while_statement break_statement elif_blocks
%type <blk> statements block else_block

/*
 * Here, we're defining the precedence of the operators.  The ones that appear
 * later have higher precedence.  All of the operators are left-associative
 * except the "not" operator, which is right-associative.
 */
%left OR
%left AND
%left PLUS MINUS
%left TIMES DIVIDEDBY
%left EQ NEQ GT GTE LT LTE
%right NOT

/* This is our goal/start symbol. */
%start program

%%

/*
 * Each of the CFG rules below recognizes a particular program construct in
 * Python and creates a new string containing the corresponding C/C++
 * translation.  Since we're allocating strings as we go, we also free them
 * as we no longer need them.  Specifically, each string is freed after it is
 * combined into a larger string.
 */
program
  : statements { target_program_ast = $1; }
  ;

statements
  : statement { $$ = new Block(); $$->statements.push_back($1); }
  | statements statement { $$->statements.push_back($2); }
  ;

statement
  : assign_statement { $$ = $1; }
  | if_statement { $$ = $1; }
  | while_statement { $$ = $1; }
  | break_statement { $$ = $1; }
  ;

primary_expression
  : IDENTIFIER { $$ = new Expr(IDENTIFIER, *$1); delete $1; }
  | FLOAT { $$ = new Expr(FLOAT, *$1); delete $1; }
  | INTEGER { $$ = new Expr(INTEGER, *$1); delete $1; }
  | BOOLEAN { $$ = new Expr(BOOLEAN, *translate_boolean_str($1)); delete $1; }
  | LPAREN expression RPAREN { $$ = $2; }
  ;

negated_expression
  : NOT primary_expression { $$ = new Expr(NOT, nullptr, nullptr, $2); }
  ;

expression
  : primary_expression { $$ = $1; }
  | negated_expression { $$ = $1; }
  | expression PLUS expression { $$ = new Expr(PLUS, "", $1, $3); }
  | expression MINUS expression { $$ = new Expr(MINUS, "", $1, $3); }  
  | expression TIMES expression { $$ = new Expr(TIMES, "", $1, $3); }
  | expression DIVIDEDBY expression { $$ = new Expr(DIVIDEDBY, "", $1, $3); }
  | expression EQ expression { $$ = new Expr(EQ, "", $1, $3); }
  | expression NEQ expression { $$ = new Expr(NEQ, "", $1, $3); }
  | expression GT expression { $$ = new Expr(GT, "", $1, $3); }
  | expression GTE expression { $$ = new Expr(GTE, "", $1, $3); }
  | expression LT expression { $$ = new Expr(LT, "", $1, $3); }
  | expression LTE expression { $$ = new Expr(LTE, "", $1, $3); }
  ;

assign_statement
  : IDENTIFIER ASSIGN expression NEWLINE { $$ = new Statement(ASSIGN, new Expr(IDENTIFIER, *$1), $3); delete $1;  }
  ;

block
  : INDENT statements DEDENT { $$ = $2; }
  ;

condition
  : expression { $$ = $1; }
  | condition AND condition { $$ = new Expr(AND, nullptr, $1, $3); }
  | condition OR condition { $$ = new Expr(OR, nullptr, $1, $3); }
  ;

if_statement
  : IF condition COLON NEWLINE block elif_blocks else_block { $$ = new Statement(IF, nullptr, nullptr, $2, $5); insertElif($$, $6, $7); }
  ;

elif_blocks
  : %empty { $$ = nullptr; }
  | elif_blocks ELIF condition COLON NEWLINE block { $$ = new Statement(IF, nullptr, nullptr, $3, $6, nullptr, $1); }
  ;

else_block
  : %empty { $$ = nullptr; }
  | ELSE COLON NEWLINE block { $$ = $4; }


while_statement
  : WHILE condition COLON NEWLINE block { $$ = new Statement(WHILE, nullptr, nullptr, $2, $5); }
  ;

break_statement
  : BREAK NEWLINE { $$ = new Statement(BREAK); }
  ;

%%

void yyerror(YYLTYPE* loc, const char* err) {
  std::cerr << "Error (line " << loc->first_line << "): " << err << std::endl;
}

/*
 * This function translates a Python boolean value into the corresponding
 * C++ boolean value.
 */
std::string* translate_boolean_str(std::string* boolean_str) {
  if (*boolean_str == "True") {
    return new std::string("1");
  } else {
    return new std::string("0");
  }
}

void insertElse(Statement *elif, Block *el) {
	if (elif->elif) {
		insertElse(elif->elif, el);
	} else {
		elif->el = el;
	}
}

void insertElif(Statement *s, Statement *elif, Block *el) {
	if (elif) {
		s->elif = elif;
		if (el) {
			insertElse(elif, el);
		}
	} else {
		s->el = el;
	}
}
