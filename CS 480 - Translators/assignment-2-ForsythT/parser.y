%{
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <set>

#include "parser.hpp"

bool _error = false;
std::set<std::string> ids;
extern int yylex();
void yyerror(YYLTYPE* loc, const char* err) {
	std::cerr << "Error (line " << loc->first_line << "): " << err << std::endl;
}
%}

%locations
%define parse.error verbose

%define api.pure full
%define api.push-pull push

%union {
	char* str;
	char* f;
	char* i;
	int category;
	char* boolean;
}

%token <str> IDENTIFIER
%token <f> FLOAT
%token <i> INTEGER
%token <boolean> BOOLEAN
%token <category> BREAK DEF ELIF ELSE FOR IF RETURN WHILE AND OR
%token <category> ASSIGN PLUS MINUS TIMES DIVIDEDBY EQ NEQ GT GTE LT LTE NOT
%token <category> LPAREN RPAREN COMMA COLON
%token <category> NEWLINE INDENT DEDENT

%type <str> program build statement condition expression then elif_state

%left AND OR
%left EQ NEQ GT GTE LT LTE NOT
%left PLUS MINUS
%left TIMES DIVIDEDBY

%start program

%%

program 
	: build { 
			if (!_error) {
				printf("#include <iostream>\nint main() {\n");
				for (auto x : ids) {
					printf("double %s;\n", x.c_str());
				}
				printf("\n/* Begin program */\n\n");
				printf("%s", $1);
				printf("\n/* End program */\n\n");
				for (auto x : ids) {
					printf("std::cout << \"%s: \" << %s << std::endl;\n", x.c_str(), x.c_str());
				}
				printf("}\n");
			}
		}

build
	: build statement { char* buf = (char*)malloc(sizeof(char) * (strlen($1) + strlen($2) + 1)); sprintf(buf, "%s%s", $1, $2); free($1); free($2); $$ = buf;}
	| statement { $$ = $1; }
	;

statement
	: IDENTIFIER ASSIGN expression NEWLINE { char* buf = (char*)malloc(sizeof(char) * (strlen($1) + strlen($3) + 6)); sprintf(buf, "%s = %s;\n", $1, $3); ids.emplace(std::string($1)); free($1); free($3); $$ = buf; }
	| IF condition COLON NEWLINE then { char* buf = (char*)malloc(sizeof(char) * (strlen($2) + strlen($5) + 9)); sprintf(buf, "if (%s) {\n%s", $2, $5); free($2); free($5); $$ = buf; }
	| WHILE condition COLON NEWLINE INDENT build DEDENT { char* buf = (char*)malloc(sizeof(char) * (strlen($2) + strlen($6) + 14)); sprintf(buf, "while (%s) {\n%s}\n", $2, $6); free($2); free($6); $$ = buf; }
	| BREAK NEWLINE { char* buf = (char*)malloc(sizeof(char) * 8); sprintf(buf, "break;\n"); $$ = buf; }
	| error NEWLINE { std::cerr << "Error: bad statement on line " << @1.first_line << std::endl; _error = true;}
	;

then
	: INDENT build DEDENT { char* buf = (char*)malloc(sizeof(char) * (strlen($2) + 3)); sprintf(buf, "%s}\n", $2); free($2); $$ = buf; }
	| INDENT build DEDENT elif_state { char* buf = (char*)malloc(sizeof(char) * (strlen($2) + strlen($4) + 3)); sprintf(buf, "%s} %s", $2, $4); free($2); free($4); $$ = buf; }
	;

elif_state
	: ELIF condition COLON NEWLINE then { char* buf = (char*)malloc(sizeof(char) * (strlen($2) + strlen($5) + 16)); sprintf(buf, "else if (%s) {\n%s}\n", $2, $5); free($2); free($5); $$ = buf; }
	| ELSE COLON NEWLINE INDENT build DEDENT { char* buf = (char*)malloc(sizeof(char) * (strlen($5) + 10)); sprintf(buf, "else {\n%s}\n", $5); free($5); $$ = buf; }
	;

condition
	: LPAREN condition RPAREN { char* buf = (char*)malloc(sizeof(char) * (strlen($2) + 3)); sprintf(buf, "(%s)", $2); $$ = buf; }
	| condition AND condition { char* buf = (char*)malloc(sizeof(char) * (strlen($1) + strlen($3) + 5)); sprintf(buf, "%s && %s", $1, $3); $$ = buf; }
	| condition OR condition { char* buf = (char*)malloc(sizeof(char) * (strlen($1) + strlen($3) + 5)); sprintf(buf, "%s || %s", $1, $3); $$ = buf; }
	| expression { $$ = $1; }
	;

expression
	: LPAREN expression RPAREN { char* buf = (char*)malloc(sizeof(char) * (strlen($2) + 3)); sprintf(buf, "(%s)", $2); free($2); $$ = buf; }
	| NOT expression { char* buf = (char*)malloc(sizeof(char) * (strlen($2) + 2)); sprintf(buf, "!%s", $2); free($2); $$ = buf; }
	| expression EQ expression { char* buf = (char*)malloc(sizeof(char) * (strlen($1) + strlen($3) + 5)); sprintf(buf, "%s == %s", $1, $3); free($1); free($3); $$ = buf; }
	| expression NEQ expression { char* buf = (char*)malloc(sizeof(char) * (strlen($1) + strlen($3) + 5)); sprintf(buf, "%s != %s", $1, $3); free($1); free($3); $$ = buf; }
	| expression GT expression { char* buf = (char*)malloc(sizeof(char) * (strlen($1) + strlen($3) + 4)); sprintf(buf, "%s > %s", $1, $3); free($1); free($3); $$ = buf; }
	| expression GTE expression { char* buf = (char*)malloc(sizeof(char) * (strlen($1) + strlen($3) + 5)); sprintf(buf, "%s >= %s", $1, $3); free($1); free($3); $$ = buf; }
	| expression LT expression { char* buf = (char*)malloc(sizeof(char) * (strlen($1) + strlen($3) + 4)); sprintf(buf, "%s < %s", $1, $3); free($1); free($3); $$ = buf; }
	| expression LTE expression { char* buf = (char*)malloc(sizeof(char) * (strlen($1) + strlen($3) + 5)); sprintf(buf, "%s <= %s", $1, $3); free($1); free($3); $$ = buf; }
	| expression PLUS expression { char* buf = (char*)malloc(sizeof(char) * (strlen($1) + strlen($3) + 4)); sprintf(buf, "%s + %s", $1, $3); free($1); free($3); $$ = buf; }
	| expression MINUS expression { char* buf = (char*)malloc(sizeof(char) * (strlen($1) + strlen($3) + 4)); sprintf(buf, "%s - %s", $1, $3); free($1); free($3); $$ = buf; }
	| expression TIMES expression { char* buf = (char*)malloc(sizeof(char) * (strlen($1) + strlen($3) + 4)); sprintf(buf, "%s * %s", $1, $3); free($1); free($3); $$ = buf; }
	| expression DIVIDEDBY expression { char* buf = (char*)malloc(sizeof(char) * (strlen($1) + strlen($3) + 4)); sprintf(buf, "%s / %s", $1, $3); free($1); free($3); $$ = buf; }
	| INTEGER { $$ = $1; /*printf("INT: %s\t%s\n", $1, $$);*/ }
	| FLOAT { $$ = $1; /*printf("FLOAT: %s\t%s\n", $1, $$);*/} 
	| BOOLEAN { $$ = $1; /*printf("BOOL: %s\t%s\n", $1, $$);*/}
	| IDENTIFIER { $$ = $1; /*ids.insert(strdup($1));*/ /*printf("ID: %s\t%s\t%s\n", $1, $$);*/} 

%%

