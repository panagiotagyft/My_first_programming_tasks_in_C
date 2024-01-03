#ifndef TYPES_H
#define TYPES_H

struct line {
	int n_tabs;
	int line_no;
	struct token_list *token;
};

struct token_list{
	char *token;
	struct token_list *next;
};

struct variables{
	long int val;
	char *str;
};


extern struct variables *var;
extern struct line    *array;

#endif // TYPES_H
