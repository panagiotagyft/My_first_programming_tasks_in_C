#ifndef INTERPRETER_H
#define INTERPRETER_H

#include "types.h"
#include "store.h"

void print(struct token_list* );
int check4(struct token_list*);
int check5(struct token_list* , struct variables *, int);
int check6(struct token_list*);
int check7(struct token_list*);
void arg(struct token_list*, struct variables *, int, char **, int);
void agc(struct token_list* , struct variables *, int, int);
void ran(struct token_list*, struct variables *, int);
void variables(struct token_list*, struct variables *, int);
void read(struct token_list*, struct variables *, int);
void write(struct token_list*, struct variables *, int);
void writeln(struct token_list*, struct variables *, int);
int while_loop(struct variables *, struct line *, int, int, int, int, int, int, char **);
int while_loop_cond(struct token_list*, struct variables *, struct line *, int, int, char **);
int if_s(struct variables *, struct line *, int, int, int, int, int, int, char **);
int if_c(struct token_list*, struct variables *, struct line *, int, int, char **);


#endif // INTERPRETER_H
