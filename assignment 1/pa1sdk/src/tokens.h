#ifndef _LIGER_TOKENS_H_
#define _LIGER_TOKENS_H_

enum {
      ID = 256,
      NUM,
      STR,
      VAR,
      COMMA,
      PERIOD,
      COLON,
      SEMICOLON,
      LPAREN,
      RPAREN,
      LSQUARE,
      RSQUARE,
      LCURLY,
      RCURLY,
      PLUS,
      MINUS,
      DIVIDE,
      MOD,
      MULTIPLY,
      OR, //|
      AND, //&
      LESSEQ, //<=
	  GREATEREQ, //>=
	  EQEQ, //==
	  NOTEQ, //!=
	  LESS, //<
      GREATER, //>
	  EQ, //=
	  NOT, //!
      IF,
      COMMENT,
      LMULTICOMMENT,
	  RMULTICOMMENT,
      TYPE,
      INT,
      BOOL,
      ELSE,
      FOR,
      TO,
      WHILE,
      NIL,
      TRU, //TRUE
      FALS, //FALSE
      MAIN,
      FUNCTION,
      RETURN,
};

extern char* yytext;

extern int yylex(void);

#endif
