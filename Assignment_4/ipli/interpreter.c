#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "types.h"
#include "store.h"
#include "interpreter.h"


int check4(struct token_list* list){
	int i;
	char *check[]={"read", "write", "writeln", "if", "else", "while", "random", "argument size", "argument"};
	for(i=0; i<9; i++){
		if (strcmp(check[i], list->token) == 0) { return i;}     //what command is?
	}
	return -1;
}

int check5(struct token_list* list, struct variables *var, int n){
	int i,u;                                                              //is a variable? if YES which variable is? else if is a number return -1
	for(i=0; i<n; i++){
		if (strcmp(var[i].str, list->token) == 0) { return i;}    //which variable is?
	
	}
     return -1;
}

int check6(struct token_list* list){
	int i;
	char *check[]={"+", "-", "*", "/", "%", "=", "==", "!=", "<", ">", "<=", ">="};
	for(i=0; i<12; i++){                                      //which symbol is?
		if (strcmp(check[i], list->token) == 0) {  return i;}
	}
}

int check7(struct token_list* list){
	int m=atoi(list->token);         //convert string to integer 
	return m;
}
//.......................................................argument................................................................
void arg(struct token_list* list, struct variables *var, int n, char *argv[], int i){
	int a, b, c;
	while(list != NULL){
		list=list->next;
		a=check7(list);   //which varint is?
		b=atoi(argv[a+i]); 
		list=list->next;
		c=check5(list, var, n);
		var[c].val=b;
		list=list->next;
	}
}
/*.......................................................argument size.............................................................*/
void agc(struct token_list* list, struct variables *var, int n, int argc){
	int c;
	while(list != NULL){
		c=check5(list, var, n);
		list=list->next;
		var[c].val=argc;
		list=list->next;
	}
}

/*.......................................................RANDOM.............................................................*/
void ran(struct token_list* list, struct variables *var, int n){
	int i;
	while(list != NULL){
		list=list->next;
		i=check5(list, var, n);
        var[i].val=rand();   //rand number
        list=list->next;
	}
}

/*.......................................................VARIABLES.............................................................*/

void variables(struct token_list* list, struct variables *var, int n ){
	int a, b, a1, c, c1, c2;
	while(list!=NULL){
		a=check5(list, var, n);
		list=list->next;
		b=check6(list);    //b=0 -> +  , b=1 -> -  , b=2 -> * , b=3 -> / , b=4 -> % , b=5 -> =...
		list=list->next;
		if(b=5 && list->next==NULL){
			a1=check5(list, var, n);
			if(a1==-1) {
				c=check7(list);
				var[a].val=c;
			}
			else{ var[a].val=var[a1].val; }
			list=list->next;
		}
		else{
			a1=check5(list, var, n);  //is a variable? if YES which variable is? else if is a number return -1
			if(a1==-1) {
				c1=check7(list);    //convert string to number
			}
			else{ c1=var[a1].val; }
			list=list->next;
			b=check6(list);     //+? =? -?...
			list=list->next;
			a1=check5(list, var, n);
			if(a1==-1) {
				c2=check7(list);
			}
			else{ c2=var[a1].val; }
			if(b==0){ var[a].val= c1 + c2; }
			if(b==1){ var[a].val= c1 - c2; }
			if(b==2){ var[a].val= c1 * c2; }
			if(b==3){ var[a].val= c1 / c2; }
			if(b==4){ var[a].val= c1 % c2; }
			list=list->next;
		}
    }
}
//..............................................READ.................................................................
void read(struct token_list* list, struct variables *var, int n ){
	int i;
	while(list!=NULL){
		list=list->next;
		i=check5(list, var, n);
		scanf("%ld", &var[i].val);    
		list=list->next;
	}
}

//..............................................WRITE.................................................................
void write(struct token_list* list, struct variables *var, int n ) {
	int i;
	while(list!=NULL){
		list=list->next;
		i=check5(list, var, n);
		printf("%ld ", var[i].val);  //print the val and one space
		list=list->next;
	}
}

//..............................................WRITELN.................................................................
void writeln(struct token_list* list, struct variables *var, int n ) {
	int i;
	while(list!=NULL){
		list=list->next;
		i=check5(list, var, n);
		printf("%ld\n", var[i].val);  //print the val and \n
		list=list->next;
	}
}

/*........................................................WHILE..................................................................*/

int while_loop(struct variables *var, struct line *array, int i , int n, int c, int count_lin, int a, int b, char *argv[]){
	int j, r4, u=0, x=0, y=0, g=0;
	if(b==6){ //b=6--> ==
		while(var[a].val == c){
			for(j=i+1; j<=count_lin; j++){
				if(array[j].token != NULL){
					r4=check4(array[j].token);  
				    if(r4==-1){ 
    	    				if (strcmp(argv[1], "-v") == 0) {
				                printf("  %3d: ", array[j].line_no); 
				                for(g=0; g< array[j].n_tabs; g++) { printf("  ");}
							    print(array[j].token);}
					variables(array[j].token, var, n); }
				    if(r4==1) { 
    	    				if (strcmp(argv[1], "-v") == 0) {
				                printf("  %3d: ", array[j].line_no); 
				                for(g=0; g< array[j].n_tabs; g++) { printf("  ");}
							    print(array[j].token);}
					write(array[j].token, var, n); }
				    if(r4==2) { 
    	    				if (strcmp(argv[1], "-v") == 0) {
				                printf("  %3d: ", array[j].line_no); 
				                for(g=0; g< array[j].n_tabs; g++) { printf("  ");}
							    print(array[j].token);}
					writeln(array[j].token, var, n); }
				    if(r4==3) { 
    	    				if (strcmp(argv[1], "-v") == 0) {
				                printf("  %3d: ", array[j].line_no); 
				                for(g=0; g< array[j].n_tabs; g++) { printf("  ");}
							    print(array[j].token);}
					        j=if_c(array[j].token, var, array, n, j, argv); }
				    if(r4==4) { 
    	    				if (strcmp(argv[1], "-v") == 0) {
				                printf("  %3d: ", array[j].line_no); 
				                for(g=0; g< array[j].n_tabs; g++) { printf("  ");}
							    print(array[j].token);}
					        continue; }
				    if(r4==5) { 
    	    				if (strcmp(argv[1], "-v") == 0) {
				                printf("  %3d: ", array[j].line_no); 
				                for(g=0; g< array[j].n_tabs; g++) { printf("  ");}
							    print(array[j].token);}			
					j=while_loop_cond(array[j].token, var, array, n, j, argv); }
				    if(r4==6) { 
    	    				if (strcmp(argv[1], "-v") == 0) {
				                printf("  %3d: ", array[j].line_no); 
				                for(g=0; g< array[j].n_tabs; g++) { printf("  ");}
							    print(array[j].token);}
					ran(array[j].token, var, n); }
			    }
		    }
		    while_loop(var, array, i, n, c, count_lin, a, b,argv);
	    }
	}
	if(b==7){ //b=7--> !=
		while(var[a].val != c){
			for(j=i+1; j<=count_lin; j++){
				if(array[j].token != NULL){
					r4=check4(array[j].token);  
				    if(r4==-1){ 
    	    				if (strcmp(argv[1], "-v") == 0) {
				                printf("  %3d: ", array[j].line_no); 
				                for(g=0; g< array[j].n_tabs; g++) { printf("  ");}
							    print(array[j].token);}
					variables(array[j].token, var, n); }
				    if(r4==1) { 
    	    				if (strcmp(argv[1], "-v") == 0) {
				                printf("  %3d: ", array[j].line_no); 
				                for(g=0; g< array[j].n_tabs; g++) { printf("  ");}
							    print(array[j].token);}
					write(array[j].token, var, n); }
				    if(r4==2) { 
    	    				if (strcmp(argv[1], "-v") == 0) {
				                printf("  %3d: ", array[j].line_no); 
				                for(g=0; g< array[j].n_tabs; g++) { printf("  ");}
							    print(array[j].token);}
					writeln(array[j].token, var, n); }
				    if(r4==3) { 
    	    				if (strcmp(argv[1], "-v") == 0) {
				                printf("  %3d: ", array[j].line_no); 
				                for(g=0; g< array[j].n_tabs; g++) { printf("  ");}
							    print(array[j].token);}
					        j=if_c(array[j].token, var, array, n, j, argv); }
				    if(r4==4) { 
    	    				if (strcmp(argv[1], "-v") == 0) {
				                printf("  %3d: ", array[j].line_no); 
				                for(g=0; g< array[j].n_tabs; g++) { printf("  ");}
							    print(array[j].token);}
					        continue; }
				    if(r4==5) { 
    	    				if (strcmp(argv[1], "-v") == 0) {
				                printf("  %3d: ", array[j].line_no); 
				                for(g=0; g< array[j].n_tabs; g++) { printf("  ");}
							    print(array[j].token);}			
					j=while_loop_cond(array[j].token, var, array, n, j, argv); }
				    if(r4==6) { 
    	    				if (strcmp(argv[1], "-v") == 0) {
				                printf("  %3d: ", array[j].line_no); 
				                for(g=0; g< array[j].n_tabs; g++) { printf("  ");}
							    print(array[j].token);}
					ran(array[j].token, var, n); }
			    }
		    }
		    while_loop(var, array, i, n, c, count_lin, a, b, argv);
	    }
	}
	if(b==8){ //b=8--> <
		while(var[a].val < c){
			for(j=i+1; j<=count_lin; j++){
				if(array[j].token != NULL){
					r4=check4(array[j].token); 
				    if(r4==-1){ 
    	    				if (strcmp(argv[1], "-v") == 0) {
				                printf("  %3d: ", array[j].line_no); 
				                for(g=0; g< array[j].n_tabs; g++) { printf("  ");}
							    print(array[j].token);}
					variables(array[j].token, var, n); }
				    if(r4==1) { 
    	    				if (strcmp(argv[1], "-v") == 0) {
				                printf("  %3d: ", array[j].line_no); 
				                for(g=0; g< array[j].n_tabs; g++) { printf("  ");}
							    print(array[j].token);}
					write(array[j].token, var, n); }
				    if(r4==2) { 
    	    				if (strcmp(argv[1], "-v") == 0) {
				                printf("  %3d: ", array[j].line_no); 
				                for(g=0; g< array[j].n_tabs; g++) { printf("  ");}
							    print(array[j].token);}
					writeln(array[j].token, var, n); }
				    if(r4==3) { 
    	    				if (strcmp(argv[1], "-v") == 0) {
				                printf("  %3d: ", array[j].line_no); 
				                for(g=0; g< array[j].n_tabs; g++) { printf("  ");}
							    print(array[j].token);}
					        j=if_c(array[j].token, var, array, n, j, argv); }
				    if(r4==4) { 
    	    				if (strcmp(argv[1], "-v") == 0) {
				                printf("  %3d: ", array[j].line_no); 
				                for(g=0; g< array[j].n_tabs; g++) { printf("  ");}
							    print(array[j].token);}
					        continue; }
				    if(r4==5) { 
    	    				if (strcmp(argv[1], "-v") == 0) {
				                printf("  %3d: ", array[j].line_no); 
				                for(g=0; g< array[j].n_tabs; g++) { printf("  ");}
							    print(array[j].token);}			
					j=while_loop_cond(array[j].token, var, array, n, j, argv); }
				    if(r4==6) { 
    	    				if (strcmp(argv[1], "-v") == 0) {
				                printf("  %3d: ", array[j].line_no); 
				                for(g=0; g< array[j].n_tabs; g++) { printf("  ");}
							    print(array[j].token);}
					ran(array[j].token, var, n); }
			    }
		    }
		    while_loop(var, array, i, n, c, count_lin, a, b, argv);
	    }
	}
	if(b==9){ //b=9 --> >
		while(var[a].val > c){
			for(j=i+1; j<=count_lin; j++){
				if(array[j].token != NULL){
					r4=check4(array[j].token); 
				    if(r4==-1){ 
    	    				if (strcmp(argv[1], "-v") == 0) {
				                printf("  %3d: ", array[j].line_no); 
				                for(g=0; g< array[j].n_tabs; g++) { printf("  ");}
							    print(array[j].token);}
					variables(array[j].token, var, n); }
				    if(r4==1) { 
    	    				if (strcmp(argv[1], "-v") == 0) {
				                printf("  %3d: ", array[j].line_no); 
				                for(g=0; g< array[j].n_tabs; g++) { printf("  ");}
							    print(array[j].token);}
					write(array[j].token, var, n); }
				    if(r4==2) { 
    	    				if (strcmp(argv[1], "-v") == 0) {
				                printf("  %3d: ", array[j].line_no); 
				                for(g=0; g< array[j].n_tabs; g++) { printf("  ");}
							    print(array[j].token);}
					writeln(array[j].token, var, n); }
				    if(r4==3) { 
    	    				if (strcmp(argv[1], "-v") == 0) {
				                printf("  %3d: ", array[j].line_no); 
				                for(g=0; g< array[j].n_tabs; g++) { printf("  ");}
							    print(array[j].token);}
					        j=if_c(array[j].token, var, array, n, j, argv); }
				    if(r4==4) { 
    	    				if (strcmp(argv[1], "-v") == 0) {
				                printf("  %3d: ", array[j].line_no); 
				                for(g=0; g< array[j].n_tabs; g++) { printf("  ");}
							    print(array[j].token);}
					        continue; }
				    if(r4==5) { 
    	    				if (strcmp(argv[1], "-v") == 0) {
				                printf("  %3d: ", array[j].line_no); 
				                for(g=0; g< array[j].n_tabs; g++) { printf("  ");}
							    print(array[j].token);}			
					j=while_loop_cond(array[j].token, var, array, n, j, argv); }
				    if(r4==6) { 
    	    				if (strcmp(argv[1], "-v") == 0) {
				                printf("  %3d: ", array[j].line_no); 
				                for(g=0; g< array[j].n_tabs; g++) { printf("  ");}
							    print(array[j].token);}
					ran(array[j].token, var, n); }
			    }
		    }
		    while_loop(var, array, i, n, c, count_lin, a, b, argv);
	    }
	}
	if(b==10){ //b=10--> <=
		while(var[a].val <= c){
			for(j=i+1; j<=count_lin; j++){
				if(array[j].token != NULL){
					r4=check4(array[j].token); 
				    if(r4==-1){ 
    	    				if (strcmp(argv[1], "-v") == 0) {
				                printf("  %3d: ", array[j].line_no); 
				                for(g=0; g< array[j].n_tabs; g++) { printf("  ");}
							    print(array[j].token);}
					variables(array[j].token, var, n); }
				    if(r4==1) { 
    	    				if (strcmp(argv[1], "-v") == 0) {
				                printf("  %3d: ", array[j].line_no); 
				                for(g=0; g< array[j].n_tabs; g++) { printf("  ");}
							    print(array[j].token);}
					write(array[j].token, var, n); }
				    if(r4==2) { 
    	    				if (strcmp(argv[1], "-v") == 0) {
				                printf("  %3d: ", array[j].line_no); 
				                for(g=0; g< array[j].n_tabs; g++) { printf("  ");}
							    print(array[j].token);}
					writeln(array[j].token, var, n); }
				    if(r4==3) { 
    	    				if (strcmp(argv[1], "-v") == 0) {
				                printf("  %3d: ", array[j].line_no); 
				                for(g=0; g< array[j].n_tabs; g++) { printf("  ");}
							    print(array[j].token);}
					        j=if_c(array[j].token, var, array, n, j, argv); }
				    if(r4==4) { 
    	    				if (strcmp(argv[1], "-v") == 0) {
				                printf("  %3d: ", array[j].line_no); 
				                for(g=0; g< array[j].n_tabs; g++) { printf("  ");}
							    print(array[j].token);}
					        continue; }
				    if(r4==5) { 
    	    				if (strcmp(argv[1], "-v") == 0) {
				                printf("  %3d: ", array[j].line_no); 
				                for(g=0; g< array[j].n_tabs; g++) { printf("  ");}
							    print(array[j].token);}			
					j=while_loop_cond(array[j].token, var, array, n, j, argv); }
				    if(r4==6) { 
    	    				if (strcmp(argv[1], "-v") == 0) {
				                printf("  %3d: ", array[j].line_no); 
				                for(g=0; g< array[j].n_tabs; g++) { printf("  ");}
							    print(array[j].token);}
					ran(array[j].token, var, n); }
			    }
		    }
		    while_loop(var, array, i, n, c, count_lin, a, b, argv);
	    }
	}
	if(b==11){  //b=11--> >=
		while(var[a].val >= c){
			for(j=i+1; j<=count_lin; j++){
				if(array[j].token != NULL){
					r4=check4(array[j].token); 
				    if(r4==-1){ 
    	    				if (strcmp(argv[1], "-v") == 0) {
				                printf("  %3d: ", array[j].line_no); 
				                for(g=0; g< array[j].n_tabs; g++) { printf("  ");}
							    print(array[j].token);}
					variables(array[j].token, var, n); }
				    if(r4==1) { 
    	    				if (strcmp(argv[1], "-v") == 0) {
				                printf("  %3d: ", array[j].line_no); 
				                for(g=0; g< array[j].n_tabs; g++) { printf("  ");}
							    print(array[j].token);}
					write(array[j].token, var, n); }
				    if(r4==2) { 
    	    				if (strcmp(argv[1], "-v") == 0) {
				                printf("  %3d: ", array[j].line_no); 
				                for(g=0; g< array[j].n_tabs; g++) { printf("  ");}
							    print(array[j].token);}
					writeln(array[j].token, var, n); }
				    if(r4==3) { 
    	    				if (strcmp(argv[1], "-v") == 0) {
				                printf("  %3d: ", array[j].line_no); 
				                for(g=0; g< array[j].n_tabs; g++) { printf("  ");}
							    print(array[j].token);}
					        j=if_c(array[j].token, var, array, n, j, argv); }
				    if(r4==4) { 
    	    				if (strcmp(argv[1], "-v") == 0) {
				                printf("  %3d: ", array[j].line_no); 
				                for(g=0; g< array[j].n_tabs; g++) { printf("  ");}
							    print(array[j].token);}
					        continue; }
				    if(r4==5) { 
    	    				if (strcmp(argv[1], "-v") == 0) {
				                printf("  %3d: ", array[j].line_no); 
				                for(g=0; g< array[j].n_tabs; g++) { printf("  ");}
							    print(array[j].token);}			
					j=while_loop_cond(array[j].token, var, array, n, j, argv); }
				    if(r4==6) { 
    	    				if (strcmp(argv[1], "-v") == 0) {
				                printf("  %3d: ", array[j].line_no); 
				                for(g=0; g< array[j].n_tabs; g++) { printf("  ");}
							    print(array[j].token);}
					ran(array[j].token, var, n); }
			    }
		    }
		    while_loop(var, array, i, n, c, count_lin, a, b, argv);
	    }
	}
	return count_lin;
}
int while_loop_cond(struct token_list* list, struct variables *var, struct line *array, int n , int i, char *argv[]){
	int a, b,c, a1, y, x=0, p;
	int count_lin=i, u=0;
	while(list!=NULL){
		list=list->next;
		a=check5(list, var, n);  //which variable is?
		list=list->next;
		b=check6(list);
		list=list->next;
		a1=check5(list, var, n);
		if(a1==-1){ c=check7(list); }
		else{ c=var[a1].val;}
		list=list->next;
	}
	y=i;
	while(y < n){
		x=array[i].n_tabs;
		
		if(array[++y].n_tabs>x && u==0){   //how many lines does it have?
			count_lin++;
		}
		else{ u++; }
	}
	p=while_loop(var, array, i, n, c, count_lin, a, b, argv);
	return count_lin;
}

/*......................................................IF.....................................................................*/

int if_s(struct variables *var, struct line *array, int i , int n, int c, int count_lin, int a, int b, char *argv[]){
	int j, r4, r, u=0, x=0, y=0, g=0;
	if(b==6){  //==
		if(var[a].val == c){
			for(j=i+1; j<=count_lin; j++){
				if(array[j].token != NULL){
					r4=check4(array[j].token); 
				    if(r4==-1){ 
    	    				if (strcmp(argv[1], "-v") == 0) {
				                printf("  %3d: ", array[j].line_no); 
				                for(g=0; g< array[j].n_tabs; g++) { printf("  ");}
							    print(array[j].token);}
					        variables(array[j].token, var, n); }
				    if(r4==1) { 
    	    				if (strcmp(argv[1], "-v") == 0) {
				                printf("  %3d: ", array[j].line_no); 
				                for(g=0; g< array[j].n_tabs; g++) { printf("  ");}
							    print(array[j].token);}
					write(array[j].token, var, n); }
				    if(r4==2) { 
    	    				if (strcmp(argv[1], "-v") == 0) {
				                printf("  %3d: ", array[j].line_no); 
				                for(g=0; g< array[j].n_tabs; g++) { printf("  ");}
							    print(array[j].token);}
					writeln(array[j].token, var, n); }
				    if(r4==3) { 
    	    				if (strcmp(argv[1], "-v") == 0) {
				                printf("  %3d: ", array[j].line_no); 
				                for(g=0; g< array[j].n_tabs; g++) { printf("  ");}
							    print(array[j].token);}
					        j=if_c(array[j].token, var, array, n, j, argv); }
				    if(r4==4) { 
    	    				if (strcmp(argv[1], "-v") == 0) {
				                printf("  %3d: ", array[j].line_no); 
				                for(g=0; g< array[j].n_tabs; g++) { printf("  ");}
							    print(array[j].token);}
					        continue; }
				    if(r4==5) { 
    	    				if (strcmp(argv[1], "-v") == 0) {
				                printf("  %3d: ", array[j].line_no); 
				                for(g=0; g< array[j].n_tabs; g++) { printf("  ");}
							    print(array[j].token);}			
					j=while_loop_cond(array[j].token, var, array, n, j, argv); }
				    if(r4==6) { 
    	    				if (strcmp(argv[1], "-v") == 0) {
				                printf("  %3d: ", array[j].line_no); 
				                for(g=0; g< array[j].n_tabs; g++) { printf("  ");}
							    print(array[j].token);}
					ran(array[j].token, var, n); }
			    }
		    }
		    if(j!=n){
		    	r=check4(array[count_lin+1].token);
		        if(r==4){
		        	count_lin++;
		    	    y=count_lin;
	                while(y < n){
	                	x=array[y].n_tabs;
	            	    if(array[++y].n_tabs>x && u==0){
	            	    	count_lin++;
		                }
		                else{ u++; }
	                } 	
			    }
		    }
	    }
	}
	if(b==7){ //!=
		if(var[a].val != c){	
			for(j=i+1; j<=count_lin; j++){
				if(array[j].token != NULL){
					r4=check4(array[j].token); 
				    if(r4==-1){ 
    	    				if (strcmp(argv[1], "-v") == 0) {
				                printf("  %3d: ", array[j].line_no); 
				                for(g=0; g< array[j].n_tabs; g++) { printf("  ");}
							    print(array[j].token);}
					variables(array[j].token, var, n); }
				    if(r4==1) { 
    	    				if (strcmp(argv[1], "-v") == 0) {
				                printf("  %3d: ", array[j].line_no); 
				                for(g=0; g< array[j].n_tabs; g++) { printf("  ");}
							    print(array[j].token);}
					write(array[j].token, var, n); }
				    if(r4==2) { 
    	    				if (strcmp(argv[1], "-v") == 0) {
				                printf("  %3d: ", array[j].line_no); 
				                for(g=0; g< array[j].n_tabs; g++) { printf("  ");}
							    print(array[j].token);}
					writeln(array[j].token, var, n); }
				    if(r4==3) { 
    	    				if (strcmp(argv[1], "-v") == 0) {
				                printf("  %3d: ", array[j].line_no); 
				                for(g=0; g< array[j].n_tabs; g++) { printf("  ");}
							    print(array[j].token);}
					        j=if_c(array[j].token, var, array, n, j, argv); }
				    if(r4==4) { 
    	    				if (strcmp(argv[1], "-v") == 0) {
				                printf("  %3d: ", array[j].line_no); 
				                for(g=0; g< array[j].n_tabs; g++) { printf("  ");}
							    print(array[j].token);}
					        continue; }
				    if(r4==5) { 
    	    				if (strcmp(argv[1], "-v") == 0) {
				                printf("  %3d: ", array[j].line_no); 
				                for(g=0; g< array[j].n_tabs; g++) { printf("  ");}
							    print(array[j].token);}			
					j=while_loop_cond(array[j].token, var, array, n, j, argv); }
				    if(r4==6) { 
    	    				if (strcmp(argv[1], "-v") == 0) {
				                printf("  %3d: ", array[j].line_no); 
				                for(g=0; g< array[j].n_tabs; g++) { printf("  ");}
							    print(array[j].token);}
					ran(array[j].token, var, n); }
			    }
		    }
		    if(j!=n){
		    	r=check4(array[count_lin+1].token);
		        if(r==4){
		        	count_lin++;
		    	    y=count_lin;
	                while(y < n){
	                	x=array[y].n_tabs;
	            	    if(array[++y].n_tabs>x && u==0){
	            	    	count_lin++;
		                }
		                else{ u++; }
	                } 	
			    }
		    }
	    }
	}
	if(b==8){ // <
		if(var[a].val < c){
			for(j=i+1; j<=count_lin; j++){
				if(array[j].token != NULL){
					r4=check4(array[j].token); 
				    if(r4==-1){ 
    	    				if (strcmp(argv[1], "-v") == 0) {
				                printf("  %3d: ", array[j].line_no); 
				                for(g=0; g< array[j].n_tabs; g++) { printf("  ");}
							    print(array[j].token);}
					variables(array[j].token, var, n); }
				    if(r4==1) { 
    	    				if (strcmp(argv[1], "-v") == 0) {
				                printf("  %3d: ", array[j].line_no); 
				                for(g=0; g< array[j].n_tabs; g++) { printf("  ");}
							    print(array[j].token);}
					write(array[j].token, var, n); }
				    if(r4==2) { 
    	    				if (strcmp(argv[1], "-v") == 0) {
				                printf("  %3d: ", array[j].line_no); 
				                for(g=0; g< array[j].n_tabs; g++) { printf("  ");}
							    print(array[j].token);}
					writeln(array[j].token, var, n); }
				    if(r4==3) { 
    	    				if (strcmp(argv[1], "-v") == 0) {
				                printf("  %3d: ", array[j].line_no); 
				                for(g=0; g< array[j].n_tabs; g++) { printf("  ");}
							    print(array[j].token);}
					        j=if_c(array[j].token, var, array, n, j, argv); }
				    if(r4==4) { 
    	    				if (strcmp(argv[1], "-v") == 0) {
				                printf("  %3d: ", array[j].line_no); 
				                for(g=0; g< array[j].n_tabs; g++) { printf("  ");}
							    print(array[j].token);}
					        continue; }
				    if(r4==5) { 
    	    				if (strcmp(argv[1], "-v") == 0) {
				                printf("  %3d: ", array[j].line_no); 
				                for(g=0; g< array[j].n_tabs; g++) { printf("  ");}
							    print(array[j].token);}			
					j=while_loop_cond(array[j].token, var, array, n, j, argv); }
				    if(r4==6) { 
    	    				if (strcmp(argv[1], "-v") == 0) {
				                printf("  %3d: ", array[j].line_no); 
				                for(g=0; g< array[j].n_tabs; g++) { printf("  ");}
							    print(array[j].token);}
					ran(array[j].token, var, n); }
			    }
		    }
		    if(j!=n){
		    	r=check4(array[count_lin+1].token);
		        if(r==4){
		        	count_lin++;
		    	    y=count_lin;
	                while(y < n){
	                	x=array[y].n_tabs;
	            	    if(array[++y].n_tabs>x && u==0){
	            	    	count_lin++;
		                }
		                else{ u++; }
	                } 	
			    }
		    }
	    }
	}
	if(b==9){ // >
		if(var[a].val > c){
			for(j=i+1; j<=count_lin; j++){
				if(array[j].token != NULL){
					r4=check4(array[j].token); 
				    if(r4==-1){ 
    	    				if (strcmp(argv[1], "-v") == 0) {
				                printf("  %3d: ", array[j].line_no); 
				                for(g=0; g< array[j].n_tabs; g++) { printf("  ");}
							    print(array[j].token);}
					variables(array[j].token, var, n); }
				    if(r4==1) { 
    	    				if (strcmp(argv[1], "-v") == 0) {
				                printf("  %3d: ", array[j].line_no); 
				                for(g=0; g< array[j].n_tabs; g++) { printf("  ");}
							    print(array[j].token);}
					write(array[j].token, var, n); }
				    if(r4==2) { 
    	    				if (strcmp(argv[1], "-v") == 0) {
				                printf("  %3d: ", array[j].line_no); 
				                for(g=0; g< array[j].n_tabs; g++) { printf("  ");}
							    print(array[j].token);}
					writeln(array[j].token, var, n); }
				    if(r4==3) { 
    	    				if (strcmp(argv[1], "-v") == 0) {
				                printf("  %3d: ", array[j].line_no); 
				                for(g=0; g< array[j].n_tabs; g++) { printf("  ");}
							    print(array[j].token);}
					        j=if_c(array[j].token, var, array, n, j, argv); }
				    if(r4==4) { 
    	    				if (strcmp(argv[1], "-v") == 0) {
				                printf("  %3d: ", array[j].line_no); 
				                for(g=0; g< array[j].n_tabs; g++) { printf("  ");}
							    print(array[j].token);}
					        continue; }
				    if(r4==5) { 
    	    				if (strcmp(argv[1], "-v") == 0) {
				                printf("  %3d: ", array[j].line_no); 
				                for(g=0; g< array[j].n_tabs; g++) { printf("  ");}
							    print(array[j].token);}			
					j=while_loop_cond(array[j].token, var, array, n, j, argv); }
				    if(r4==6) { 
    	    				if (strcmp(argv[1], "-v") == 0) {
				                printf("  %3d: ", array[j].line_no); 
				                for(g=0; g< array[j].n_tabs; g++) { printf("  ");}
							    print(array[j].token);}
					ran(array[j].token, var, n); }
			    }
		    }
		    if(j!=n){
		    	r=check4(array[count_lin+1].token);
		        if(r==4){
		        	count_lin++;
		    	    y=count_lin;
	                while(y < n){
	                	x=array[y].n_tabs;
	            	    if(array[++y].n_tabs>x && u==0){
	            	    	count_lin++;
		                }
		                else{ u++; }
	                } 	
			    }
		    }		    
	    }
	}
	if(b==10){ // <=
		if(var[a].val <= c){
			for(j=i+1; j<=count_lin; j++){
				if(array[j].token != NULL){
					r4=check4(array[j].token); 
				    if(r4==-1){ 
    	    				if (strcmp(argv[1], "-v") == 0) {
				                printf("  %3d: ", array[j].line_no); 
				                for(g=0; g< array[j].n_tabs; g++) { printf("  ");}
							    print(array[j].token);}
					variables(array[j].token, var, n); }
				    if(r4==1) { 
    	    				if (strcmp(argv[1], "-v") == 0) {
				                printf("  %3d: ", array[j].line_no); 
				                for(g=0; g< array[j].n_tabs; g++) { printf("  ");}
							    print(array[j].token);}
					write(array[j].token, var, n); }
				    if(r4==2) { 
    	    				if (strcmp(argv[1], "-v") == 0) {
				                printf("  %3d: ", array[j].line_no); 
				                for(g=0; g< array[j].n_tabs; g++) { printf("  ");}
							    print(array[j].token);}
					writeln(array[j].token, var, n); }
				    if(r4==3) { 
    	    				if (strcmp(argv[1], "-v") == 0) {
				                printf("  %3d: ", array[j].line_no); 
				                for(g=0; g< array[j].n_tabs; g++) { printf("  ");}
							    print(array[j].token);}
					        j=if_c(array[j].token, var, array, n, j, argv); }
				    if(r4==4) { 
    	    				if (strcmp(argv[1], "-v") == 0) {
				                printf("  %3d: ", array[j].line_no); 
				                for(g=0; g< array[j].n_tabs; g++) { printf("  ");}
							    print(array[j].token);}
					        continue; }
				    if(r4==5) { 
    	    				if (strcmp(argv[1], "-v") == 0) {
				                printf("  %3d: ", array[j].line_no); 
				                for(g=0; g< array[j].n_tabs; g++) { printf("  ");}
							    print(array[j].token);}			
					j=while_loop_cond(array[j].token, var, array, n, j, argv); }
				    if(r4==6) { 
    	    				if (strcmp(argv[1], "-v") == 0) {
				                printf("  %3d: ", array[j].line_no); 
				                for(g=0; g< array[j].n_tabs; g++) { printf("  ");}
							    print(array[j].token);}
					ran(array[j].token, var, n); }
			    }
		    }
		    if(j!=n){
		    	r=check4(array[count_lin+1].token);
		        if(r==4){
		        	count_lin++;
		    	    y=count_lin;
	                while(y < n){
	                	x=array[y].n_tabs;
	            	    if(array[++y].n_tabs>x && u==0){
	            	    	count_lin++;
		                }
		                else{ u++; }
	                } 	
			    }
		    }
	    }
	}
	if(b==11){ // >=
	    if(var[a].val >= c){
			for(j=i+1; j<=count_lin; j++){
				if(array[j].token != NULL){
					r4=check4(array[j].token); 
				    if(r4==-1){ 
    	    				if (strcmp(argv[1], "-v") == 0) {
				                printf("  %3d: ", array[j].line_no); 
				                for(g=0; g< array[j].n_tabs; g++) { printf("  ");}
							    print(array[j].token);}
					variables(array[j].token, var, n); }
				    if(r4==1) { 
    	    				if (strcmp(argv[1], "-v") == 0) {
				                printf("  %3d: ", array[j].line_no); 
				                for(g=0; g< array[j].n_tabs; g++) { printf("  ");}
							    print(array[j].token);}
					write(array[j].token, var, n); }
				    if(r4==2) { 
    	    				if (strcmp(argv[1], "-v") == 0) {
				                printf("  %3d: ", array[j].line_no); 
				                for(g=0; g< array[j].n_tabs; g++) { printf("  ");}
							    print(array[j].token);}
					writeln(array[j].token, var, n); }
				    if(r4==3) { 
    	    				if (strcmp(argv[1], "-v") == 0) {
				                printf("  %3d: ", array[j].line_no); 
				                for(g=0; g< array[j].n_tabs; g++) { printf("  ");}
							    print(array[j].token);}
					        j=if_c(array[j].token, var, array, n, j, argv); }
				    if(r4==4) { 
    	    				if (strcmp(argv[1], "-v") == 0) {
				                printf("  %3d: ", array[j].line_no); 
				                for(g=0; g< array[j].n_tabs; g++) { printf("  ");}
							    print(array[j].token);}
					        continue; }
				    if(r4==5) { 
    	    				if (strcmp(argv[1], "-v") == 0) {
				                printf("  %3d: ", array[j].line_no); 
				                for(g=0; g< array[j].n_tabs; g++) { printf("  ");}
							    print(array[j].token);}			
					j=while_loop_cond(array[j].token, var, array, n, j, argv); }
				    if(r4==6) { 
    	    				if (strcmp(argv[1], "-v") == 0) {
				                printf("  %3d: ", array[j].line_no); 
				                for(g=0; g< array[j].n_tabs; g++) { printf("  ");}
							    print(array[j].token);}
					ran(array[j].token, var, n); }
			    }
		    }
		    if(j!=n){
		    	r=check4(array[count_lin+1].token);
		        if(r==4){
		        	count_lin++;
		    	    y=count_lin;
	                while(y < n){
	                	x=array[y].n_tabs;
	            	    if(array[++y].n_tabs>x && u==0){
	            	    	count_lin++;
		                }
		                else{ u++; }
	                } 	
			    }
		    }
	    }
    }
	return count_lin;
}
int if_c(struct token_list* list, struct variables *var, struct line *array, int n , int i, char *argv[]){
	int a, b,c, a1, y, x=0, p;
	int count_lin=i, u=0;
	while(list!=NULL){
		list=list->next;
		a=check5(list, var, n);
		list=list->next;
		b=check6(list);  // ==, !=, < 
		list=list->next;
		a1=check5(list, var, n);
		if(a1==-1){ c=check7(list); }
		else{ c=var[a1].val;}
		list=list->next;
	}
	y=i;
	while(y < n){
		x=array[i].n_tabs;
		
		if(array[++y].n_tabs > x && u==0){  //how many lines does it have?
			count_lin++;
		}
		else{ u++; }
	} 
	p=if_s(var, array, i, n, c, count_lin, a, b, argv);
	return p;
}
