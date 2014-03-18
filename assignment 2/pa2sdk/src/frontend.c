#include "llstruct.h"
#include "lexer.h" // yyin, yylex, etc.
#include "parser.h" // yyparse, yylval, token enum, etc
#include <string.h>

/*typedef struct functionList{
	char name[10];
	int arity;
	int defined;
	int calls;
	struct functionList *next;
}functionList;*/

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
 //linked list for functions
 functionList *list = NULL;
 //value returned by yyparse
 int returnval = 0;
 //the type of the value 0 for numeric 1 for boolean 2 for undefined
 int type = -1;
 //mode of program 0 for eval 1 for decls
 int mode = 0;
 //yyparse() returns 0 if successfull
 if(yyparse(&returnval,&type,&mode,&list))
 {
 	printf("Genuine Liger: no\n");
 }
 else
 {
 	printf("Genuine Liger: yes\n");
 	if(mode==0)
 	{
 		if(type == 2)
 		{
 			printf("Result: unknown\n");
 		}
 		else if ((type == 1)&&(returnval == TRUE || returnval == FALSE))
 		{
 			printf("Result: %s\n",returnval==TRUE?"true":"false");
 		}
 		else if (type == 0)
 		{
 			printf("Result: %d\n",returnval);
 		}
 	}

 	functionList *curr = list;
 	while(curr!=NULL)
 	{
 		printf("Function %s:\n",curr->name);
 		if(curr->arityMatch==1)
 		{
 			printf("   Arity: mismatch!\n");
 		}
 		else
 		{
 			printf("   Arity: %d\n",curr->arity);
 		}
 		if(curr->defined==1)
 		{
 			printf("   Defined: no\n");
 		}
 		else if(curr->defined==3)
 		{
 			printf("   Multiple definitions!\n");
 		}
 		else
 		{
 			printf("   Defined: yes\n");
 		}
 		printf("   Calls: %d\n",curr->calls);
 		curr = curr->next;
 	}

	
 }
return 0;
}
