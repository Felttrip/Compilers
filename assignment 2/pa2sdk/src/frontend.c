#include "lexer.h" // yyin, yylex, etc.
#include "parser.h" // yyparse, yylval, token enum, etc.

int main(int argc, char** argv) {
 //Check for correct number of files    
 if(argc != 2)
 {
   printf("Error, incorrect usage, pa2 <FILE.lig>\n");
   return 0;
 }

 //throw an error if file is unreadable
 char *fname = NULL;
 fname = argv[1];
 yyin = fopen(fname,"r");
 if(yyin == NULL)
 {
   printf("file unreadable");
   return 0;
 }
 yyparse();
return 0;
}
