#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "types.h"
#include "store.h"
#include "interpreter.h"

struct line *array;
struct variables *var;

int main (int argc, char *argv[]){
	FILE *fp;
	long curtime;
	char buf[1024];
	char  c;
	char token1[64];
	char token2[64];
	int i, l, r1, r2, r3, r4, r5, r6, v, a=1;
	char* n1;
	int k=0, n=0, x=0, y=0, count=0, u=0, g=0;
	curtime = time(NULL);
    srand((unsigned int) curtime);
	if(argc==1){
		printf("Missing arguments...\n");
		return 1;
	}
	if (strcmp(argv[1], "-v") == 0) { a++; }
	
	if ((fp = fopen(argv[a], "rb")) == NULL){
		perror("fopen source-file");
		return 1;
	}
	while (fgets(buf, 1024, fp) != NULL) {
		n++;
	}
	rewind(fp);
	if((array=malloc(n*sizeof(struct line)))==NULL){
		printf("Error:Not available memory\n");
		return 1;
	}
	
	if((var=malloc(n*sizeof(struct variables)))==NULL){
		printf("Error:Not available memory\n");
		return 1;
	}
	for(u=0; u < n; u++){
		var[u].str="\0";
	    var[u].val='\0';
	}
	u=0;
	while(fgets(buf, sizeof(buf), fp) != NULL){
		l=strlen(buf);
		
		for(i=0; i < l; i++){
			if(buf[i]=='\t'){
				count++;       //counter--> tabs
			}
			else if(buf[i]=='#') { break;}   //comment --> i don't want it 
			else if(buf[i] >= 'A' && buf[i] <= 'Z'){
					token1[x++]=buf[i];            
					if(y!=0){
						insert(&array[k].token, token2);
						for(y=0; y<64; y++){  token2[y]='\0'; } // i initialize the token2
						y=0;                                     //shows that it is empty
					}
			}
			else if(buf[i] >= '_' && buf[i] <= 'z'){
					token1[x++]=buf[i];
					if(y!=0) {
						insert(&array[k].token, token2);
						for(y=0; y<64; y++) {  token2[y]='\0';  } // i initialize the token2
						y=0;                                    //shows that it is empty
					}
			}
			else if(buf[i] >= '0' && buf[i] <= '9'){
					token1[x++]=buf[i];
					if(y!=0) {
						insert(&array[k].token, token2);   
						for(y=0; y<64; y++) {  token2[y]='\0';  } // i initialize the token2
						y=0;                                     //shows that it is empty
					}
			}
			else if(buf[i]==' ') {
					if(y!=0) {
						insert(&array[k].token, token2);
						for(y=0; y<64; y++) {  token2[y]='\0';  } // i initialize the token2
						y=0;                                       //shows that it is empty
					}
					if(x!=0){
						insert(&array[k].token, token1);
						r1=check1(token1);   //is a variable?
                        r2=check2(token1);   // check if variable is wrong
                        if(r2==44){ return 1;}
						if(r1==0 && r2==1){
							r3=check3(var, token1, n);
							if(r3==0){
								var[u].str=malloc((strlen(token1)+1) * sizeof(char));
			                    strcpy(var[u].str, token1);
			                    u++;
							}
						}
						for(x=0; x<64; x++){ token1[x]='\0'; }
						x=0;
					}										
			}			
			else{
					token2[y++]=buf[i];
					if(x!=0){
						insert(&array[k].token, token1);
						r1=check1(token1);
                        r2=check2(token1);
                        if(r2==44){ return 1;}
						if(r1==0 && r2==1){
							r3=check3(var, token1, n);
							if(r3==0){
								var[u].str=malloc((strlen(token1)+1) * sizeof(char));
			                    strcpy(var[u].str, token1);
			                    u++;
							}
					    }
						for(x=0; x<64; x++){ token1[x]='\0'; }
						x=0;
					}
			}
			
		}
		for(y=0; y<64; y++) {  token2[y]='\0';  }
		for(x=0; x<64; x++){ token1[x]='\0'; }
		x=0; y=0;
		array[k].line_no=k;
		array[k].n_tabs=count;
	    k++;
	    count=0;
	}
	fclose(fp);

		for(i=0; i < n; i++){
			if(array[i].token!=NULL){
				r4=check4(array[i].token); 
				if(r4==-1){ 
    	    		if (strcmp(argv[1], "-v") == 0) {  //print the line
				        printf("  %3d: ", array[i].line_no); 
				        for(g=0; g< array[i].n_tabs; g++) { printf("  ");}
						print(array[i].token);}
				    variables(array[i].token, var, n); }
		        if(r4==0){ 
    	    		if (strcmp(argv[1], "-v") == 0) {
				        printf("  %3d: ", array[i].line_no);  //print the line
				        for(g=0; g< array[i].n_tabs; g++) { printf("  ");}
						print(array[i].token);}              
			        read(array[i].token, var, n);  //r4=0 --> read
			    }
				if(r4==1) { 
    	    		if (strcmp(argv[1], "-v") == 0) {
				        printf("  %3d: ", array[i].line_no); //print the line
				        for(g=0; g< array[i].n_tabs; g++) { printf("  ");}
						print(array[i].token);}
				    write(array[i].token, var, n); } //r4=1 --> write
				if(r4==2) { 
    	    		if (strcmp(argv[1], "-v") == 0) {
				        printf("  %3d: ", array[i].line_no); //print the line
				        for(g=0; g< array[i].n_tabs; g++) { printf("  ");}
						print(array[i].token);}
				    writeln(array[i].token, var, n); }  //r4=2--> writeln
				if(r4==3) { 
    	    		if (strcmp(argv[1], "-v") == 0) {
				        printf("  %3d: ", array[i].line_no); //print the line
				        for(g=0; g< array[i].n_tabs; g++) { printf("  ");}
						print(array[i].token);}   
				    i=if_c(array[i].token, var, array, n, i, argv); } // //r4=3--> if
				if(r4==4) {
    	    		if (strcmp(argv[1], "-v") == 0) {
				        printf("  %3d: ", array[i].line_no); //print the line
				        for(g=0; g< array[i].n_tabs; g++) { printf("  ");}
						print(array[i].token);}
				    continue; }      //r4=4--> else
				if(r4==5) {
    	    		if (strcmp(argv[1], "-v") == 0) {
				        printf("  %3d: ", array[i].line_no);  //print the line
				        for(g=0; g< array[i].n_tabs; g++) { printf("  ");}
						print(array[i].token);}
				    i=while_loop_cond(array[i].token, var, array, n, i, argv); }  //r4=5--> while
				if(r4==6) { 
    	    		if (strcmp(argv[1], "-v") == 0) {
				        printf("  %3d: ", array[i].line_no);   //print the line 
				        for(g=0; g< array[i].n_tabs; g++) { printf("  ");}
						print(array[i].token);}
				    ran(array[i].token, var, n);}   //r4=6--> random
				if(r4==7) { 
    	    		if (strcmp(argv[1], "-v") == 0) {
				        printf("  %3d: ", array[i].line_no);   //print the line
				        for(g=0; g< array[i].n_tabs; g++) { printf("  ");}
						print(array[i].token);}
				    agc(array[i].token, var, n, argc); }
				if(r4==8) { 
    	    		if (strcmp(argv[1], "-v") == 0) {
				        printf("  %3d: ", array[i].line_no);   //print the line
				        for(g=0; g< array[i].n_tabs; g++) { printf("  ");}
						print(array[i].token);}
				    arg(array[i].token, var, n, argv, a); }
			}
		}
	return 0;
}
