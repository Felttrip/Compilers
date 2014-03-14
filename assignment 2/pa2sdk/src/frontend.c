#include "lexer.h" // yyin, yylex, etc.
#include "parser.h" // yyparse, yylval, token enum, etc
#include <string.h>

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
 yylval.bool_val = -1;
 //yyparse() returns 0 if successfull
 if(yyparse())
 {
 	printf("Genuine Liger: no\n");
 }
 else
 {
 	printf("Genuine Liger: yes\n");
 	if (yylval.bool_val == -1)
 	{
 		printf("Results: %d\n",yylval.val);
 	}
 	else
 	{
 		printf("Results: %s\n",yylval.bool_val==TRUE?"True":"False");
 	}
 	
 }
return 0;
}
