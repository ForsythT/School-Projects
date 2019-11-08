%{
	#include <stdio.h>
	#include <stdlib.h>
	#include <string.h>
	#include <stack>

	std::stack<int> indents;
%}

BOOL (True|False)

IDS ([a-z]|[A-Z]|_)([a-z]|[A-Z]|[0-9]|_)*

INT ("-")?([0-9])+

FLOAT ("-")?([0-9])+"."([0-9])*

%option yylineno
%option noyywrap

%%

^((" "|\t)*\n)	{}

^[^ \t]*	{
			while (indents.size() > 0) {	
				indents.pop();
				printf("DEDENT\n");
			}
			
			REJECT;
		}

^(" "|\t)*	{
			if (indents.size() > 0) {
				if (yyleng > indents.top()) {
					indents.push(yyleng);
					printf("INDENT\n");
				} else if (yyleng < indents.top()) {
					indents.pop();
					printf("DEDENT\n");
				}
			} else {
				indents.push(yyleng);
				printf("INDENT\n");
			}

			REJECT;
		}

[ \t]*		{}

\n		{ printf("NEWLINE\n"); }

(#)(.)*(\n)	{}

"and"		{ printf("AND\t\t%s\n", yytext); }
"break"		{ printf("BREAK\t\t%s\n", yytext); }
"def"		{ printf("DEF\t\t%s\n", yytext); }
"elif"		{ printf("ELIF\t\t%s\n", yytext); }
"else"		{ printf("ELSE\t\t%s\n", yytext); }
"for"		{ printf("FOR\t\t%s\n", yytext); }
"if"		{ printf("IF\t\t%s\n", yytext); }
"not"		{ printf("NOT\t\t%s\n", yytext); }
"or"		{ printf("OR\t\t%s\n", yytext); }
"return"	{ printf("RETURN\t\t%s\n", yytext); }
"while"		{ printf("WHILE\t\t%s\n", yytext); }

{BOOL}		{
			bool b;
			if (strcmp("True", yytext) == 0) {
				b = true;
			} else {
				b = false;
			}
			printf("BOOLEAN\t\t%d\n", b);
		}

{IDS}		{ printf("IDENTIFIER\t%s\n", yytext); }

{INT}		{
			int i = atoi(yytext);
			printf("INTEGER\t\t%i\n", i);
		}

{FLOAT}		{
			double f = atof(yytext);
			printf("FLOAT\t\t%f\n", f);
		}

"="		{ printf("ASSIGN\t\t%s\n", yytext); }
"+"		{ printf("PLUS\t\t%s\n", yytext); }
"-"		{ printf("MINUS\t\t%s\n", yytext); }
"*"		{ printf("TIMES\t\t%s\n", yytext); }
"/"		{ printf("DIVIDEDBY\t%s\n", yytext); }
"=="		{ printf("EQ\t\t%s\n", yytext); }
"!="		{ printf("NEQ\t\t%s\n", yytext); }
">"		{ printf("GT\t\t%s\n", yytext); }
">="		{ printf("GTE\t\t%s\n", yytext); }
"<"		{ printf("LT\t\t%s\n", yytext); }
"<="		{ printf("LTE\t\t%s\n", yytext); }

"("		{ printf("LPAREN\t\t%s\n", yytext); }
")"		{ printf("RPAREN\t\t%s\n", yytext); }
","		{ printf("COMMA\t\t%s\n", yytext); }
":"		{ printf("COLON\t\t%s\n", yytext); }

.		{ printf("Symbol not recognized: %s\n", yytext); }

<<EOF>>		{
			while (indents.size() > 0) {
				indents.pop();
				printf("DEDENT\n");
			}

			return 0;
		}

%%

int main() {
	yylex();
}
