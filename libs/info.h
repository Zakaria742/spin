#ifndef _INFO_H
#define _INFO_H

typedef struct terminal_info{
  int cols;
  int rows;
}tinfo;

typedef struct choices_info{
  char **words;
  int total;
}chinfo;

#endif
