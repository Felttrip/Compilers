/*Nathaniel Thompson
  Megan Ritchey
  Compilers Assignment 1*/

//Include statements for tokens and needed librarys   
#include "tokens.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define STACK_MAX 100

//extern yylex() and yyin used from flex
extern int yylex(void);
extern FILE *yyin;

//Stack structure used for keeping track of 
//curly brackets, square brackets, and parentheses
struct _Stack{
      int data[STACK_MAX];
      int size;
};
typedef struct _Stack Stack;

//Push and Pop functions used with stack
void Stack_Push(Stack *s, int d);
int Stack_Pop(Stack *s, int d);

//array of the token names in string form
char *toknames[] = {"ID","NUM","STR","VAR","COMMA","PERIOD","COLON","SEMICOLON","LPAREN","RPAREN","LSQUARE",
                    "RSQUARE","LCURLY","RCURLY","PLUS","MINUS","DIVIDE","MOD","MULTIPLY","OR","AND","LESSEQ","GREATEREQ", 
                    "EQEQ","NOTEQ", "LESS","GREATER", "EQ","NOT","IF","COMMENT","LMULTICOMMENT","RMULTICOMMENT","TYPE","INT",
                    "BOOL","ELSE","FOR","TO","WHILE","NIL","TRU", "FALS","MAIN","FUNCTION","RETURN","NEWLINE","BADTOKEN"};

//main function
int main(int argc, char** argv) 
{
      //variables used while parsing
      char *fname;
      int tok;
      int numTok = 0;
      int mainFlag = 0;
      int brackFlag = 0;
      //used for bonus
      int lineNum = 1;
      int lastTok = -1;
      Stack *bracketStack = malloc(sizeof(Stack));
      bracketStack->size = 0;

      //Check for correct number of arguments
      if(argc != 2)
      {
      	printf("Error, incorrect usage, pa1 <FILE.lig>\n");
      	return 0;
      }

      //Open file for reading
      fname = argv[1];
      yyin = fopen(fname,"r");
      if(yyin == NULL)
      {
      	printf("file unreadable");
      	return 0;
      }
      
      //Loop forever, we will leave this loop when tok==0
      for(;;)
      {
            //Read next token from yylex()
            tok = yylex();
            //leave loop if we are out of tokens
            if(tok==0)
                  break;
            //Add one to number of tokens
            numTok++;
            //Compare token to one of several special cases
            switch(tok)
            {
                  //Check for Main, only set main flag if last token was function 
                  case FUNCTION:
                  {
                        lastTok = numTok;
                        break;
                  }
                  case MAIN: 
                  {
                        if(lastTok == (numTok-1))
                        {
                              mainFlag = 1;
                        }      
                        break;
                  }
                  //Keeping track of number and order of parentheses and brackets
                  case LPAREN: 
                  {
                        Stack_Push(bracketStack,LPAREN);
                        break;
                  }
                  case RPAREN:
                  {
                        if(!brackFlag)
                              brackFlag = Stack_Pop(bracketStack,RPAREN);
                        break;
                  }
                  case LCURLY:
                  {
                        Stack_Push(bracketStack,LCURLY);      
                        break;
                  }
                  case RCURLY:
                  {
                        if(!brackFlag)
                              brackFlag = Stack_Pop(bracketStack,RCURLY);
                        break;
                  }
                  case LSQUARE:
                  {
                        Stack_Push(bracketStack,LSQUARE);
                        break;
                  }
                  case RSQUARE:
                  {
                        if(!brackFlag)
                              brackFlag = Stack_Pop(bracketStack,RSQUARE);
                        break;
                  }
                  //Handling multiline comments
                  case LMULTICOMMENT:
                  {
                        //decrement the token counter
                        numTok--;
                        //throw away tokens untill comment is finished
                        while(RMULTICOMMENT != (tok = yylex()))
                        {
                              //still keep track of line number
                              if(tok==NEWLINE)
                                    lineNum++;
                        }
                        break;
                  }
                  //Keeping track of line numbers
                  case NEWLINE:
                  {
                        numTok--;
                        lineNum++;
                        break;
                  }
                  //Throw a message for bad tokens and do not count them
                  // BONUS line number is thrown 
                  case BADTOKEN:
                  {
                        numTok--;
                        printf(" on line %d\n",lineNum);
                        break;
                  }
                  //Throw a message for IDs over 32 chars and do not count them
                  case ID:
                  {
                        if(strlen(yytext)>32)
                        {
                              numTok--;
                              printf("ID %s too long, ID not counted\n",yytext);
                        }
                        break;
                  }
                  //Throw a message for Strings over 255 char and do not count them
                  case STR:
                  {
                        if(strlen(yytext)>255)
                        {
                              numTok--;
                              printf("String Literal %s too long, String Literal not counted\n",yytext);
                        }
                        break;
                  }
                  //Throw a message for numbers greater than 2^32-1 and do not count them
                  case NUM:
                  {
                        if((atoi(yytext)<0)||(atoi(yytext)>(pow(2,32)-1)))
                        {
                              numTok--;
                              printf("Error invalid number\n");
                        }     
                  }

            }

      }

      //print out the final message for number of tokens, main existing, and brackets matching
      printf("Total tokens: %d\n",numTok);
      printf("Main declared: %s\n",mainFlag?"yes":"no");
      printf("All brackets match: %s\n",brackFlag?"no":"yes");
      return 0;
}

//Stack push function
void Stack_Push(Stack *s, int d)
{
      if(s->size < STACK_MAX)
            s->data[s->size++] = d;
      else
            printf("Error, stack is full\n");

}

//stack pop function
int Stack_Pop(Stack *s, int d)
{
      if(s->size<=0)
      {
            printf("Error, attempting to pop an empty stack\n");
            return -1;
      }
      //Switch case to throw errors when brackets and parentheses dont match up
      switch(d)
      {
            case RPAREN:
            {
                  if(s->data[s->size-1]==LPAREN)
                  {
                        s->size--;
                        return 0;
                  }
                  else
                        return 1;
            }
            case RCURLY:
            {
                  if(s->data[s->size-1]==LCURLY)
                  {
                        s->size--;
                        return 0;
                  }
                  else
                        return 1;
            }
            case RSQUARE:
            {
                  if(s->data[s->size-1]==LSQUARE)
                  {
                        s->size--;
                        return 0;
                  }
                  else
                        return 1;
            }
            default:
                  return -1;

      }
}
