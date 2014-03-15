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
 //value returned by yyparse
 int returnval;
 //the type of the value 0 for numeric 1 for boolean 2 for undefined
 int type = -1;
 //yyparse() returns 0 if successfull
 if(yyparse(&returnval,&type))
 {
 	printf("Genuine Liger: no\n");
 }
 else
 {
 	printf("Genuine Liger: yes\n");
 	if(type == 2)
 	{
 		printf("Results: Undefined\n");

 	}
 	else if ((type == 1)&&(returnval == TRUE || returnval == FALSE))
 	{
 		printf("Results: %s\n",returnval==TRUE?"True":"False");
 		
 	}
 	else if (type == 0)
 	{
 		printf("Results: %d\n",returnval);
 	}

	
 }
return 0;
}
