%code top {

#include <stdio.h>
#include <string.h>
#include "parser.h"

// Defined in the C file generated by flex. We can't include lexer.h because
// that'd cause a circular dependency (we need the header generated by bison to
// generate the lexer.h header).
extern int yylex(void);

static void yyerror(const char*);

}

// These get stuck in a token enum in the header bison generates (parser.h),
// which we can then include in our lexer spec.
%token VAR TYPE FUNCTION
      FOR TO WHILE IF ELSE RETURN
      NIL TRUE FALSE
      INT BOOL
      ID STR NUM
      UNKNOWN
      EVAL

// These associate tokens with string lits like "<=" so we can use them in our
// grammar.
%token LT_EQ "<="
%token GT_EQ ">="
%token EQ "=="
%token NOT_EQ "!="

// The type of yylval.
%union {
      int val;
};

// The top-level rule.
%start program

%%

// A Liger program is either a list of declarations or it's an "extended Liger"
// program -- an EVAL token followed by a Liger expression.
program: 
      decls
      | EVAL '(' exp ')' ';'

decls: 

exp:

%%

void yyerror(const char* p) {
      fprintf(stderr, "%s\n", p);
}

