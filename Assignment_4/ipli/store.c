#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "types.h"
#include "store.h"
#include "interpreter.h"

void  insert(struct token_list* *ptraddr, char *buf) {
	while (*ptraddr != NULL) {
		ptraddr= &((*ptraddr)->next); 
	}
	*ptraddr = malloc(sizeof(struct token_list));                    //add element
	(*ptraddr)->token = malloc((strlen(buf)+1) * sizeof(char));
    strcpy((*ptraddr)->token, buf);
    (*ptraddr)->next = NULL;
}

void print(struct token_list* list) {
	while (list != NULL) {
    printf("%s ", list->token);
    list = list->next; }
    printf("\n");
}

int check1(char *str){
	int i;
	char *check[]={"read", "write", "writeln", "if", "else", "while", "random", "argument size", "argument"};
	for(i=0; i<9; i++){
		if (strcmp(check[i], str) == 0) { return 1;}  //what command is?
	}
	return 0;
}

int check2(char *str){
	int x;
	for(x=0; x<64; x++){
        if(str[x]=='$') {return 44;}
	}
	if(str[0] >= 'A' && str[0] <= 'Z') { return 1;}    //the variable is wrong?
    if(str[0] >= 'a' && str[0] <= 'z') { return 1;}
    if( str[0]=='_'){ return 44;}
    
}

int check3(struct variables *var, char *str, int n){
	int i;
	for(i=0; i<n; i++){
		if (strcmp(var[i].str, str) == 0) { return 1;}  //is the same?
	}
	return 0;
}
