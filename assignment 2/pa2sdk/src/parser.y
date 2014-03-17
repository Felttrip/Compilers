%{

#include <stdio.h>
#include <string.h>
#include "parser.h"
#define YYERROR_VERBOSE

// Defined in the C file generated by flex. We can't include lexer.h because
// that'd cause a circular dependency (we need the header generated by bison to
// generate the lexer.h header).
extern int yylex(void);
static void yyerror( int *returnval, int *type, const char* p);
extern char* undef;


%}
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

//values sent to yyparse() they are pointers so we can change them later to returnvalues from yyparse()
%parse-param {int *returnval} {int *type}

// The type of yylval.
%union {
      int val;
};



//Type
%type <val> NUM INT 

%left '|'
%left '&'
%left GR_EQ NOT_EQ
%left '>' '<' LT_EQ GT_EQ
%left '+' '-'
%left '*' '/' '%'
%left UPLUS UMINUS '!'
// The top-level rule.
%start program

%%

// A Liger program is either a list of declarations or it's an "extended Liger"
// program -- an EVAL token followed by a Liger expression.
program: 
      decls 
      | EVAL '(' exp ')' ';'

//Declarations
decls:
      decls1
      |

decls1:
      decls1 globalDec
      |globalDec

globalDec:
       VAR argDec decEnd ';'
       |TYPE argDec decEnd';'
       |func 



func:
      FUNCTION ID '(' funcArgList ')' returnType '{' localDecls statementList '}'

returnType:
      ':' type 
      |

statement:
      exp ';'
      |RETURN returning ';' 
      |statementAssignment ';'
      |IF '(' exp ')' '{' statementList '}' elseChunk
      |WHILE '(' exp ')' '{' statementList '}'
      |FOR '(' assignment TO exp ')' '{' statementList '}'

statementAssignment:
      leftAssignment '=' exp

leftAssignment:
      ID
      |structFieldLookUp
      |arraySubscript

arraySubscript:
      lArraySub '[' exp ']'

lArraySub:
      ID
      |commaSepArray
      |callingFunc
      |arraySubscript
      |structFieldLookUp

commaSepArray:
      '[' paramList ']' 

elseChunk:
      ELSE '{' statementList '}'
      |

returning:
      '(' exp ')' 
      |      

statementList:
      statementList1
      |

statementList1:
      statement
      |statementList1 statement 

argDec:
      ID ':' type


structFieldLookUp:
      lStructLookUp '.' ID

lStructLookUp:
      callingFunc
      |structureLiteral
      |arraySubscript
      |structFieldLookUp
      |ID

funcArgList:
      funcArgList1
      |

funcArgList1:
      argDec
      |funcArgList1 ',' argDec

type:
      INT
      |BOOL
      |'[' type ']'
      |ID
      |structureType
      //fill in more possible stuct

callingFunc:
      ID '(' paramList ')'

paramList:
      paramList1
      |

paramList1:
      exp
      |paramList1 ',' exp


localDecls:
      localDecls1
      |

localDecls1:
      localDec
      |localDecls1 localDec

localDec:
      VAR ID ':' type decEnd';'

decEnd:
      '=' exp
      |

assignment:
      ID '=' exp

assignList:
      assignList1
      |

assignList1:
      assignment
      |assignList1 ',' assignment

structureType:
      '{' funcArgList '}'

structureLiteral:
      '{' assignList '}'

exp: 
     INT
     |ID
     |NUM           //{$$ = yylval.val;}
     |NIL
     |STR
     |TRUE          //{$$ = TRUE}
     |FALSE         //{$$ = FALSE}
     |callingFunc
     |structureLiteral
     |structFieldLookUp
     |arraySubscript
     |commaSepArray
     |'(' exp ')'
     |'+' exp %prec UPLUS
     |'-' exp %prec UMINUS
     |'!' exp  
     |exp '+' exp    //{$$ = $1 + $2;}
     |exp '-' exp    //{$$ = $1 - $2;}
     |exp '*' exp    //{$$ = $1 * $2;}
     |exp '/' exp    //{$$ = $1 / $2;}
     |exp '%' exp    //{$$ = $1 % $2;}
     |exp LT_EQ exp  //{$$ = $1 <= $3 ? TRUE : FALSE ;}
     |exp GT_EQ exp  //{$$ = $1 >= $3 ? TRUE : FALSE ;}
     |exp EQ exp     //{$$ = $1 == $3 ? TRUE : FALSE ;}
     |exp NOT_EQ exp //{$$ = $1 != $3 ? TRUE : FALSE ;}
     |exp '>' exp    //{$$ = $1 > $3 ? TRUE : FALSE ;}
     |exp '<' exp    //{$$ = $1 < $3 ? TRUE : FALSE ;}
     |exp '&' exp    //{$$ = ($1 == TRUE) && ($3 == TRUE) ? TRUE : FALSE ;}
     |exp '|' exp    //{$$ = ($1 == TRUE) || ($3 == TRUE) ? TRUE : FALSE ;}
     
%%


void yyerror( int *returnval, int *type, const char* p) {
      fprintf(stderr, "%s\n", p);
}

