#include <stdio.h>
#include <stdlib.h>

#ifdef COSTS
void cost(int i, int p, int r, int m, int n, int *k, int **c, int **dp) {
	int l, count=0, j, y;
	printf("Item costs: ");
	dp[n-1][r]=-1;      /* i start from the last row and the the r column. r is the rest of the money */
	for(i=n-1; i > 0; i--) {
		for(j=0; j < k[i]; j++) {
			r=r+c[i][j];          /* i check all the costs */
			if(dp[i-1][r]==1 && count==0) {   /* examine if the position where the r (r=r+c[i][j]) of the current cost is equal with 1 */ 
				dp[i-1][r]=-1;                /* convert this position with -1 .I use -1 because after i want to print these positions */
				count++;                      /* I convert 1 to -1 for each product */
			}
			else{ r=r-c[i][j]; }   /* else check the next cost */
		}
		count=0;
	}
	/* Find the positions with -1 and print the cost.I print one cost for each product */
	for(i=0; i < n; i++) {
    	for(l=0; l < m+1; l++) {
    		if(dp[i][l]==-1 && count==0) {
    			y=m-l;
    			m=l;
			    printf("%6d", y);    /*I print one cost for each product */
			    count++;
		    }
	    }
	    count=0;
	}
	printf("\n");
}
#endif

int solve3(int i, int p, int m, int n, int *k, int **c, int **dp) {
	int j, l, x, y;
	int count=0;
	for(j=0; j < k[i]; j++) {
		if(p >= c[i][j]) {
			dp[i][p-c[i][j]]=1;       /* for the first row i save equal with 1 the position where the remainder of the current cost */
		}
	} 
	for(i=1; i < n; i++) {
		for(l=0; l < (m+1); l++) {
			if(dp[i-1][l]==1) {       /* if the position which equal with 1 */
				for(j=0; j < k[i]; j++) {
					if(l >= c[i][j]) {   /*the l is the current remainder. If the rest of the money is bigger than or equal current cost*/
						x=l-c[i][j];     /* i remove the collumn with current cost  collum is the current remainder */
						dp[i][x]=1; }    /* and i save this position with 1*/
				}
			}
		}
	}
	/* I check which position in last row is equal with 1 */
	if(i==n) {
   	for(l=0; l < m+1; l++) {
   			if(dp[i-1][l]==1) { return l;	}   /* When i find the first position which equal with 1 return l(l is the rest of the money) */

   	}
   }
}
int  shop(int M, int N, int **C, int *K) {
	    int S, R, **dp, j, l, n, m ;
	    int P=M;
	    int i=0;
	    m=M+1;
	    
		/* I crete the dynamic mem (2-dimersional array) witch i save the positives remainders of the costs */
        dp = malloc(N * sizeof(int *));
        if (dp == NULL) {
        	printf("ERROR Not available memory\n");     /* if memory cannot be allocated --> terminate the program */
        	return 1;
        }
        for (l = 0; l < N; l++) {
        	dp[l] = malloc(m * sizeof(int));
            if (dp[l] == NULL) {
            	printf("ERROR Not available memory\n");     /* if memory cannot be allocated --> terminate the program */
            	return 1;
            }
        }
        for (l = 0; l < N; l++) {
        	for(j=0; j < m; j++) {
        		dp[l][j] = 0;        /* all array element equal with 0 because i save with 1 the positive R{i}{p} */
        	}
        }
        R=solve3(i, P, M, N, K, C, dp);
		S=M-R;     /* S is the money i spent */
		if (S > 0) {
			#ifdef COSTS
			cost(i, P, R, M, N, K, C, dp);     /* cost function print the item costs */
			#endif
			printf("Maxinum amount spent is: %d\n", S);
		}
		else {
			printf("No solution found\n");    /* I dont have enough money to buy all the products */
		}
		/* dellocating the memory */
        for (l = 0 ; l < N ; l++) {
   	      free(dp[l]);
        }
        free(dp);		
}
