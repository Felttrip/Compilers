#include "tokens.h"
#include <stdio.h>
#include <stdlib.h>
#define STACK_MAX 100

extern int yylex(void);
extern FILE *yyin;



struct _Stack{
      int data[STACK_MAX];
      int size;
};
typedef struct _Stack Stack;

void Stack_Push(Stack *s, int d);
int Stack_Pop(Stack *s, int d);

char *toknames[] = {"ID","NUM","STR","VAR","COMMA","PERIOD","COLON","SEMICOLON","LPAREN","RPAREN","LSQUARE",
                    "RSQUARE","LCURLY","RCURLY","PLUS","MINUS","DIVIDE","MOD","MULTIPLY","OR","AND","LESSEQ","GREATEREQ", 
                    "EQEQ","NOTEQ", "LESS","GREATER", "EQ","NOT","IF","COMMENT","LMULTICOMMENT","RMULTICOMMENT","TYPE","INT",
                    "BOOL","ELSE","FOR","TO","WHILE","NIL","TRU", "FALS","MAIN","FUNCTION","RETURN"};

int main(int argc, char** argv) 
{
      char *fname;
      int tok;
      int numTok = 0;
      int mainFlag = 0;
      int brackFlag = 0;
      Stack *bracketStack = malloc(sizeof(Stack));
      bracketStack->size = 0;
      if(argc != 2)
      {
      	printf("Wrong number of files!");
      	return 0;
      }

      fname = argv[1];
      yyin = fopen(fname,"r");
      if(yyin == NULL)
      {
      	printf("file unreadable");
      	return 0;
      }
      
      
      for(;;)
      {
            tok = yylex();
            if(tok==0)
                  break;
            numTok++;
            switch(tok)
            {
                  case MAIN:
                        {
                              mainFlag = 1;
                              break;
                        }
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
                  case LMULTICOMMENT:
                        {
                              numTok--;
                              while(RMULTICOMMENT!=yylex()){};
                              break;
                        }
            }

      }

      printf("Total tokens: %d\n",numTok);
      printf("Main Declared: %s\n",mainFlag?"yes":"no");
      printf("All Brackets Match: %s\n",brackFlag?"no":"yes");
      return 0;
}

void Stack_Push(Stack *s, int d)
{
      if(s->size < STACK_MAX)
            s->data[s->size++] = d;
      else
            printf("STACK OVERFLOW! EVERYONE RUN!\n");

}

int Stack_Pop(Stack *s, int d)
{
      if(s->size<=0)
      {
            printf("Error stack empty\n");
            return -1;
      }
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
