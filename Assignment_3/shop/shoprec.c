#include <stdio.h>
#include <stdlib.h>

int solve1(int i, int p, int m, int n, int *k, int **c) {
	int j, q, x=3000;
	  if (p >= 0 && i == n) { return p; }      /* if the rest of the money is bigger or equal zero and i bought all the products return the current rest*/
      if (p < 0) { return m; }                 /* if the rest of the money is smaller than zero and i have not bought all the products return all money*/
      for(j=0; j < k[i]; j++) {
      	q=solve1(i+1, p-c[i][j], m, n, k, c);  /* go to other product */
      
	  	/* check the minimum rest of the money */	
      	if(q < x) {
      		x=q;                      
      	}
      }
      return x;
}
int  shop(int M, int N, int **C, int *K) {
	    int S, R, i=0;
	    int P=M;
        R=solve1(i, P, M, N, K, C);
		S=M-R;   /* S is the money i spent */
		if (S > 0) {
			printf("Maxinum amount spent is: %d\n", S);
		}
		else {
			printf("No solution found\n");        /* I dont have enough money to buy all the products */
		}
}

