#include "tokens.h"
#include <stdio.h>

extern int yylex(void);
extern FILE *yyin;

char *toknames[] = {"ID","NUM","STR","VAR","COMMA","PERIOD","COLON","SEMICOLON","LPAREN","RPAREN","LSQUARE",
                    "RSQUARE","LCURLY","RCURLY","PLUS","MINUS","DIVIDE","MOD","MULTIPLY","OR","AND","LESSEQ","GREATEREQ", 
                    "EQEQ","NOTEQ", "LESS","GREATER", "EQ","NOT","IF","COMMENT","LMULTICOMMENT","RMULTICOMMENT","TYPE","INT",
                    "BOOL","ELSE","FOR","TO","WHILE","NIL","TRU", "FALS","MAIN","FUNCTION","RETURN"};

int main(int argc, char** argv) {
      char *fname;
      int tok;
      int numTok = 0;
      int mainFlag = 0;
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
            }

      }

      printf("Total tokens: %d\n",numTok);
      printf("Main Declared: %s\n",mainFlag?"yes":"no");
      return 0;
}
