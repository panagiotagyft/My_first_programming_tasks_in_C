#include <stdio.h>
#include <stdlib.h>

#ifdef COSTS
void cost(int i, int p, int r, int m, int n, int *k, int **c, int **mem) {
	int count=0, j;
	printf("Item costs: ");
    for(i=0; i < n+1; i++) {       
    	for(j=0; j < k[i]; j++) {
    		p=p-c[i][j];              /* i check all the costs */
    		if(mem[i+1][p]==r && count==0) {     /* examine if the position where the remainder of the current cost is equal with r --> print the cost */ 
			    printf("%6d", c[i][j]);
			    count++;                         /* I print one cost for each product */
		    }
		    else{ p=p+c[i][j]; }
	    }
	    count=0;
    }
    printf("\n");
}
#endif

int solve2(int i, int p, int m, int n, int *k, int **c, int **mem) {
	int j, q, x=m;
	if (p >= 0 && i == n) { return p; }   /* if the rest of the money is bigger or equal zero and i bought all the products return the current rest*/
    if (p < 0) { return m; }              /* if the rest of the money is smaller than zero and i have not bought all the products return all money*/
    for(j=0; j < k[i]; j++) {
    	if(p >= c[i][j]) {               /* if the rest of the money is bigger than or equal current cost*/
    	    /* if current p has not been recalculated i write the p */
    		if (mem[i+1][p-c[i][j]]!=-1) {      
	  			q=mem[i+1][p-c[i][j]];
	  		}
	  		/* else go to other product */
	  		else{
	  			mem[i+1][p-c[i][j]]=solve2(i+1, p-c[i][j], m, n, k, c, mem);  
				q=mem[i+1][p-c[i][j]]; 
	  		}
	  		if(q < x) { x=q; }            /* check the minimum rest of the money */	
      	}
	}
      return x;
}

int  shop(int M, int N, int **C, int *K) {
	int S, R, **mem, j, l, n, m ;
	int P=M, i=0;
	n=N+1;
	m=M+1;
	/* I crete the dynamic mem (2-dimersional array) witch i save the differents R{i}{p}.When i need to use the differents R{i}{p} i do not count them again */
    mem = malloc(n * sizeof(int *));
    if (mem == NULL) {
    	printf("ERROR Not available memory\n");     /* if memory cannot be allocated --> terminate the program */
        return 1;
    }
    for (l = 0; l < n; l++) {
    	mem[l] = malloc(m * sizeof(int));
        if (mem[l] == NULL) {
        	printf("ERROR Not available memory\n");      /* if memory cannot be allocated --> terminate the program */
            return 1;
        }
    }
    for (l = 0; l < n; l++) {         
    	for(j=0; j < m; j++) {
    		mem[l][j] = -1;        /* all array element equal with -1 because i save the positive R{i}{p} */
        }
    }
    R=solve2(i, P, M, N, K, C, mem);
	S=M-R;            /* S is the money i spent */
	if (S > 0) {
		#ifdef COSTS
		cost(i, P, R, M, N, K, C, mem);   /* cost function print the item costs */
		#endif
		printf("Maxinum amount spent is: %d\n", S);
	}
	else {
		printf("No solution found\n");    /* I dont have enough money to buy all the products */
	}
	/* dellocating the memory */
    for (l = 0 ; l < n ; l++) {
    	free(mem[l]);
    }
    free(mem);		
}

