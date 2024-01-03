/* file: kalmpr.c */

#include <stdio.h>
#include <stdlib.h> 
#include <time.h>
#define MINNUM 2100000000
#define MAXNUM 2101000000
#define MAXK   5
#define COMPUTATIONS 20

int main()
{
	int counter_prms, current, m;            /* counter_prms --> prime counter, current --> current number, m -->multification  */
	int a=0, c=0;
	printf("./kalmpr\nChecking numbers in [%d,%d]\n\n", MINNUM, MAXNUM);
	for(current=MINNUM ; current <= MAXNUM; current++) {      /*computing the factorization of an integer from MINNUM to MAXNUM */
		int num=current;                     /* I set current equal num for modifications*/               
	    int counter_prms=0;                  /* I initialize a prime counter equal to zero*/
	    while (num % 2 == 0) {               /* I start with division by 2 (which is prime) and if num mod 2 equal zero --> 2 is a factor of the current*/
	    	counter_prms += 1;               /* if 2 is a factor --> i increase the prime counter +1*/
			num= num/2;                      /* repeat the procedure until the remainder of the division of any num by 2 (which is prime) == zero*/
	    }
	    int i;
	    for(i = 3; i*i <= num; i+=2) {       /* check for factors dividing from i=3 to i=square num, and increase the i +2 */
	    	while (num % i == 0) {           /*division by i (which is prime) and if num mod i equal zero --> i is a factor of the current*/
	    		num = num/i;
		 	    counter_prms += 1;           /* if i is a factor --> increase the prime counter +1*/
	    	}
	    }
	    if (num > 2) {                       /* if num>2 --> increase the prime counter +1 */
	    	counter_prms += 1;
	    }
	    int k=counter_prms;                  /* I set counter_prms equal k to find k almost numbers*/
	    if(k >= 2 && k <= MAXK) {            /* if 2 <= k <= MAXK -->  increase the c   +1*/
	    	c += 1;                          /* c is the counter for k almost numbers between 2 and MAXK */
	    }
	    if(k==2) {                           /* I only want 2 almost */
	    	a += 1;                          /* a is the counter for 2 almost numbers*/ 
	    	/*i want to save penultimate i (first factor) so subtract 2 --> i-2 */
	    	if((double)num*0.99 <= i-2 && i-2<num ) {   /* the first factor is not greater than 1 percent of the last factor AND (first)i-2 < (last)num */
	    		m=num*(i-2);                            /* multiply the first (i-2) and the last factor (num) */
         	    printf("%d * %d = %d is an interesting semiprime\n", i-2, num, m);
	    	}
	    }
	}
	printf("\nFound %d k-almost prime numbers 2 <= k <= %d\n", c, MAXK);
	printf("Found %d semiprimes\n\n", a);
	
	long curtime;
	int r, x, y, z;
	curtime = time(NULL);                    /* Current time (in seconds since 1/1/1970) */
    printf("Current time is %ld\n\n", curtime);
    srand((unsigned int) curtime);           /* Seed for random number generator */
	printf("Checking %d random numbers\n\n", COMPUTATIONS );
	 
	for (r=0 ; r < COMPUTATIONS ; r++) {      /* i want 20 randoms (x) */
		y = rand();                           /* Select 1st random number */
        z = rand();                           /* Select 2nd random number */
        x=((y%32768)+1) *((z%32768)+1) + 1;   /* the creation of a random number x by two random numbers y and z */  
        
		int number=x;                         /* I set x equal number for modifications*/
        int counter=0;                        /* I initialize a counter (primes) equal to zero*/
        while (number % 2 == 0) {             /* I start with division by 2 (which is prime) and if number mod 2 equal zero --> 2 is a factor of the x*/
        	number= number/2;                 /* repeat the procedure until the remainder of the division of any number by 2 (which is prime) == zero*/
			counter += 1;                     /* if 2 is a factor --> i increase the counter +1*/
        }
        int f;                             
	    for(f=3 ; f*f <= number; f+=2) {      /* check for factors dividing from f=3 to f=square number, and increase the "f +2 */
	    	while (number % f == 0){          /*division by f (which is prime) and if number mod f equal zero --> f is a factor of the x*/
		 	    number = number/f;        
		 	    counter += 1;                 /* if f is a factor --> i increase the counter +1*/
		   }
	    }
	    if (number > 2) {                     /* if number>2 --> increase the counter +1 */
	    	counter += 1;
	    }
	    printf("%10d is a %d-almost prime number\n", x, counter);
	}  
}
