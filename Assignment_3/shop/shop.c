#include <stdio.h>
#include <stdlib.h>
#include "shop.h"

int main(int argc, char *argv[]) {         
	int N, i, j, **C, S, R, M, *K; 
	M=atoi(argv[1]);             /* the first argument is the number of products.atoi return integer */
	scanf("%d", &N);             /* N is the number of products */
	K=malloc(N*sizeof(int *));   /* I create the dynamic array (K).One dimersional array.The length of the array size is N.Each element position in array contains the mumber of product models */
	if (K == NULL) {
		printf("ERROR Not available memory\n");  
		return -1;                /* if memory cannot be allocated --> terminate the program */
	}   
	/* I create the dynamic array (C). 2-dimersional array, with not equal number of columns */       
	C=malloc (N * sizeof(int *));   
	if (C == NULL) {
		printf("ERROR Not available memory\n");
		return -1;
	}
	for(i=0; i < N; i++) { 
		scanf("%d", &K[i]);
		C[i]=malloc (K[i] * sizeof(int)); /* The length of the array size is K[i] .Each element position in array contains the prices models (costs) */
	    if (C[i] == NULL) {
	    	printf("ERROR Not available memory\n");
		    return -1;
	    }
		for(j=0; j < K[i]; j++) {
			scanf("%d", &C[i][j]);     /* I write the cost on the C */
		}
	}
   shop(M,N,C,K);                  /*shop fuction calculate the rest of the money */ 
   /* dellocating the memory */
   for (i = 0 ; i < N ; i++) {
   	free(C[i]);
   }
   free(C);
   free(K);
   return 0;
}
