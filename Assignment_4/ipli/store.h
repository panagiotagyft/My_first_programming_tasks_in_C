#ifndef STORE_H
#define STORE_H

#include "types.h"


void insert(struct token_list* *, char *);

int check1(char *);
int check2(char *);
int check3(struct variables *, char *, int);
int store(struct variables *, struct line *, int, char **, int, char *, char *, char *, int );

#endif // STORE_H
