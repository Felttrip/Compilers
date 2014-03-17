#ifndef LLSTRUCT_H
#define LLSTRUCT_H

typedef struct _functionList{
  char *name;
  int arity;
  int arityMatch;
  int defined;
  int calls;
  struct _functionList *next;
}functionList;

#endif