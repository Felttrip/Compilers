%{

#include "tokens.h"

%}

%option noyywrap

%%

"var" 						{return VAR;} 
","							{return COMMA;}
"."							{return PERIOD;}
":"							{return COLON;}
";"							{return SEMICOLON;}
"("             			{return LPAREN;}
")"             			{return RPAREN;}
"["             			{return LSQUARE;}
"]"             			{return RSQUARE;}
"{"             			{return LCURLY;}
"}"             			{return RCURLY;}
"//"            			{return COMMENT;}
"/*"            			{return LMULTICOMMENT;}
"*/"            			{return RMULTICOMMENT;}
"+"             			{return PLUS;}
"-"             			{return MINUS;}
"/"             			{return DIVIDE;}
"%"             			{return MOD;}
"*"             			{return MULTIPLY;} 
"|"             			{return OR;}
"&"             			{return AND;}
"<="            			{return LESSEQ;}
">="            			{return GREATEREQ;}
"=="            			{return EQEQ;}
"!="            			{return NOTEQ;}
"<"             			{return LESS;}
">"            		 		{return GREATER;}
"="             			{return EQ;}
"!"             			{return NOT;}
"if"            			{return IF;}
"type"          			{return TYPE;}
"int"           			{return INT;}
"bool"          			{return BOOL;}
"else"          			{return ELSE;}
"for"           			{return FOR;}
"to"            			{return TO;}
"while"         			{return WHILE;}
"nil"           			{return NIL;}
"true"          			{return TRU;}
"false"         			{return FALS;}
"main"          			{return MAIN;}
"function"      			{return FUNCTION;}
"return"        			{return RETURN;}
[0-9]+						{return NUM;}
[A-Za-z][A-Za-z0-9"_"]*     {return ID;}
"\".*\""                    {return STR;} //fix space
" "							{}
"\n"						{}
. {
      // Here we match any character that wasn't already matched by preceding
      // patterns.
      fprintf(stderr, "Error: unrecognized character: %s\n", yytext);
}

%%

// More C functions and such can go down here.

