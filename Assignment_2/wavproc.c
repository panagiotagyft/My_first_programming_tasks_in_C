/* MODES : 1,2,3,4,5,6 */

#include <stdio.h>
#include <math.h>
#ifdef WIN32
#include <io.h>
#include <fcnt1.h>
#endif
/* #define MODE x , x=1,2,3,4,5,6 */

/* 4 bytes */
int fun1(int x, int y, int z, int w) { /* good.wav: x=85, y=00, z=00, w=00 */
	y = y << 8;     /* NUMBER: 00    SHIFT DIRECTION: left (<<)    BITS TO SHIFT: 8  RESULTS: 0000 */
    y = x | y;      /* y = (0085)hex */
    z = z << 16;    /* NUMBER: 00    SHIFT DIRECTION: left (<<)   BITS TO SHIFT: 16  RESULTS: 000000 */
    z = y | z;      /* z = (000085)hex */
    w = w << 24;    /* NUMBER: 00    SHIFT DIRECTION: left (<<)   BITS TO SHIFT: 16  RESULTS: 00000000 */
    w = z | w;      /* w = (00000085)hex */
    return w;
}
/* 2 bytes */
int fun2(int p, int q) {
	q = q << 8;
    q = p | q;
    return q;
}
/* 4 bytes */
int fun3(int r) {   /*for example 8bitstereo4.wav  sf=88236 (=000158AC)hex */
	    int s, t, u, v;
	    s = r & 0x000000FF;   /* 0x000158AC & 0x000000FF  RESULTS: (AC)hex */
        putchar(s);
    	t = r & 0x0000FF00;   /* 0x000158AC & 0x0000FF00  RESULTS: (5800)hex */
    	t= t >> 8;            /* NUMBER: 5800,   SHIFT DIRECTION: right(>>),   BITS TO SHIFT: 8,  RESULT:(58)hex */
    	putchar(t);
    	u = r & 0x00FF0000;   /* 0x000158AC & 0x00FF0000  RESULTS: (010000)hex */
    	u = u >> 16;          /* NUMBER: 010000,   SHIFT DIRECTION: right(>>),   BITS TO SHIFT: 16,  RESULT:(01)hex */
    	putchar(u);
    	v = r & 0xFF000000;   /* 0x000158AC & 0xFF000000  RESULTS: (00000000)hex */
		v = v >> 24;          /* NUMBER: 00000000,   SHIFT DIRECTION: right(>>),   BITS TO SHIFT: 24,  RESULT:(00)hex */
		putchar(v); 
		return r;  
}
/* 2 bytes */
int fun4(int k) {
	    int m, n;
        m = k & 0x00FF;
        putchar(m);
    	n = k & 0xFF00;
    	n = n >> 8;
    	putchar(n);
}
int main (void) 
{ int a1, a2, a3, a4, sf, b1, b2, b3, b4, sc, c1, c2, wt, d1, d2, ms, e1, e2, e3, e4, sr, f1, f2, f3, f4, bs, g1, g2, ba, mult, h1, h2, bps, i1, i2, i3, i4, sd, div, mul, ch, c;
  int count=0;
	#ifdef WIN32
	_setmode (fileno (stdout), 0_BINARY);
	_setmode (fileno (stdin), 0_BINARY);
	#endif
	
	/* RIFF */
	/* wav files starts with a signature RIFF (hex: 52, 49, 46, 46) */
	if (getchar() != 'R') { fprintf(stderr, "ERROR! 'RIFF' not found\n"); return 1;}    /* check if first byte is (52)hex 'R' else print --> error and terminate the program */ 
    if (getchar() != 'I') { fprintf(stderr, "ERROR! 'RIFF' not found\n"); return 1;}    /* check if 2nd byte is (49)hex 'I' else print --> error and terminate the program */ 
    if (getchar() != 'F') { fprintf(stderr, "ERROR! 'RIFF' not found\n"); return 1;}    /* check if 3rd byte is (46)hex 'F' else print --> error and terminate the program */ 
    if (getchar() != 'F') { fprintf(stderr, "ERROR! 'RIFF' not found\n"); return 1;}    /* check if 4th byte is (46)hex 'F' else print --> error and terminate the program */ 
    
	/*  SIZE OF FILE  */
	/* for example: good.wav */
	a1=getchar();          /* getchar: 85 */
	a2=getchar();          /* getchar: 00 */
	a3=getchar();          /* getchar: 00 */
	a4=getchar();          /* getchar: 00 */
	sf= fun1(a1, a2, a3, a4);   /* LITTLE ENDIAN --> BIG ENDIAN */
	fprintf(stderr, "size of file: %d\n", sf);  /* print sf (133)dec (= (00000085)hex) */
	
	/*  WAVE  */
	/* is a signature WAVE (hex: 57, 41, 56, 45) */
    if (getchar() != 'W') { fprintf(stderr, "ERROR! 'WAVE' not found\n"); return 1; }    /* check if 9th byte is (57)hex 'W' else print --> error and terminate the program */ 
    if (getchar() != 'A') { fprintf(stderr, "ERROR! 'WAVE' not found\n"); return 1; }    /* check if 10th byte is (41)hex 'A' else print --> error and terminate the program */ 
    if (getchar() != 'V') { fprintf(stderr, "ERROR! 'WAVE' not found\n"); return 1; }    /* check if 11th byte is (56)hex 'V' else print --> error and terminate the program */ 
    if (getchar() != 'E') { fprintf(stderr, "ERROR! 'WAVE' not found\n"); return 1; }    /* check if 12th byte is (45)hex 'E' else print --> error and terminate the program */ 
    
    /*  fmt  */
    /*Format chunk ID : "fmt " (hex: 66, 6d, 74, 20) */
    if (getchar() != 'f') { fprintf(stderr, "ERROR! 'fmt ' not found\n"); return 1; }    /* check if 13th byte is (66)hex 'f' else print --> error and terminate the program */ 
    if (getchar() != 'm') { fprintf(stderr, "ERROR! 'fmt ' not found\n"); return 1; }    /* check if 14th byte is (6d)hex 'm' else print --> error and terminate the program */ 
    if (getchar() != 't') { fprintf(stderr, "ERROR! 'fmt ' not found\n"); return 1; }    /* check if 15th byte is (74)hex 't' else print --> error and terminate the program */ 
    if (getchar() != ' ') { fprintf(stderr, "ERROR! 'fmt ' not found\n"); return 1; }    /* check if 16th byte is (20)hex ' ' else print --> error and terminate the program */ 
    
    /* SIZE OF FORMAT CHUNK */
    /* for example: good.wav */
    b1=getchar();          /* getchar: 10 */
	b2=getchar();          /* getchar: 00 */
	b3=getchar();          /* getchar: 00 */
	b4=getchar();          /* getchar: 00 */
	sc= fun1(b1, b2, b3, b4);    /* LITTLE ENDIAN --> BIG ENDIAN */
	if (sc==16) {                /* if (16)dec = (00000010)hex */
    	fprintf(stderr, "size of format chunk: %d\n", sc);   /* print sc (16)dec (= (00000010)hex ) */
    }
    else {
    	fprintf(stderr, "size of format chunk: %d\nError! size of format chunk should be 16\n", sc);   /* else print --> error and terminate the program */
    	return 1;
    }
    /* WAVE TYPE FORMAT */
    c1=getchar();     /* getchar: 01 */
	c2=getchar();     /* getchar: 00 */
	wt=fun2(c1, c2);  /* LITTLE ENDIAN --> BIG ENDIAN */
	if (wt==1) {      /* if (1)dec = (0001)hex */
    	fprintf(stderr, "WAVE type format: %d\n", wt);   /* print wt (1)dec (= (0001)hex ) */
    }
    else {
    	fprintf(stderr, "WAVE type format: %d\nError! WAVE type format should be 1\n", wt);     /* else print --> error and terminate the program */
    	return 1;
    }
    /* MONO/STEREO */
    /* for example: good.wav */
    d1 = getchar();    /* getchar: 01 */
    d2 = getchar();    /* getchar: 00*/
    ms=fun2(d1, d2);   /* LITTLE ENDIAN --> BIG ENDIAN */
    if(ms==1 || ms==2) {     /* if ms=1 or ms=2 */
    	fprintf(stderr, "mono/stereo: %d\n", ms);   /* print ms */
    }
    else {
    	fprintf(stderr, "mono/stereo: %d\nError! mono/stereo should be 1 or 2\n", ms);        /* else print --> error and terminate the program */
    	return 1;
    }
    /* SAMPLE RATE */
    e1=getchar();
	e2=getchar();
	e3=getchar();
	e4=getchar();
	sr= fun1(e1, e2, e3, e4);
	fprintf(stderr, "sample rate: %d\n", sr); 
	
	/* BYTESPERSEC */
	f1=getchar();
	f2=getchar();
	f3=getchar();
	f4=getchar();
	bs= fun1(f1, f2, f3, f4);
	fprintf(stderr, "bytes/sec: %d\n", bs);
	
	/* BLOCK ALIGNMENT */
	g1 = getchar();
    g2 = getchar();
    ba=fun2(g1, g2);
    fprintf(stderr, "block alignment: %d\n", ba);
    mult = sr * ba;    /* mult = SampleRate x BlockAlign */
    if (mult != bs) {  /* if does not equal (mult and bs (=SampleRate x BlockAlign)) */
    	fprintf(stderr, "Error! bytes/second should be sample rate x block alignment\n");  /* print --> error and terminate the program */
    	return 1;
    }
    /*  BITSPERSAMPLE  */
    h1 = getchar();
    h2 = getchar();
    bps=fun2(h1, h2);
    if(bps==8 || bps==16) {  /* if BITSPERSAMPLE is 8 or 16 */
    	fprintf(stderr, "bits/sample: %d\n", bps); }  /* print bps */
    else {
    	fprintf(stderr, "bits/sample: %d\nError! bits/sample should be 8 or 16\n", bps);   /* else print --> error and terminate the program */
    	return 1; }
    div = bps / 8;     /* BitsPerSample /8 */
    mul = div * ms;    /* mul = div(=BitsPerSample /8) * ms(Mono/Stereo) */
    if (mul != ba) {   /* if does not equal (mul and ba (=BlockAlign)) */
    	fprintf(stderr, "Error! block alignment should be bits per sample/ 8 x mono/stereo\n");  /* print --> error and terminate the program */
    	return 1; 
	}
    /* DATA */
    if (getchar() != 'd') { fprintf(stderr, "ERROR! 'data' not found\n"); return 1;}
    if (getchar() != 'a') { fprintf(stderr, "ERROR! 'data' not found\n"); return 1;}
    if (getchar() != 't') { fprintf(stderr, "ERROR! 'data' not found\n"); return 1;}
    if (getchar() != 'a') { fprintf(stderr, "ERROR! 'data' not found\n"); return 1;}
    
    /* SIZEOFDATA */
    i1=getchar();
	i2=getchar();
	i3=getchar();
	i4=getchar();
	sd= fun1(i1, i2, i3, i4);   /* LITTLE ENDIAN --> BIG ENDIAN */
	fprintf(stderr, "size of data chunk: %d\n", sd);
    
    int fn1, fn2, fn3, fn4, fn5, fn6, fn7, fn8, fn9, ch1, ch2, ch3, ch4, mo, mo1, md6, md5, md4, t1;
    if (MODE !=1) {
    	putchar('R');
    	putchar('I');
    	putchar('F');
    	putchar('F');
    }
    /* sizeoffile */
    if (MODE==2 || MODE==3 || MODE==6) {
    	putchar(a1);
    	putchar(a2);
    	putchar(a3);
    	putchar(a4); }
    if (MODE==4 || MODE==5) {
    	sf=sf-sd;       /*distance between sf and sd   for example  8bitstereo.wav: sf(size of file) =176436, sd(size of data chunk) =176400, sf=176436-176400*/
    	sd=sd/2;        /* sd=176400/2=88200 */
    	sf=sd+sf;       /* sf=88200+36=88236 */
    	fn1=fun3(sf);   /* BIG ENDIAN --> LITTLE ENDIAN */
	}
	if (MODE != 1) {
	    putchar('W');
        putchar('A');
        putchar('V');
        putchar('E'); 
	    putchar('f');
        putchar('m');
        putchar('t');
        putchar(' ');
		fn9=fun3(sc); 
	    fn2=fun4(wt); }
	/* mono/stereo */
	if(MODE==2 || MODE==3 || MODE==6) {
		fn3=fun4(ms); }
	if(MODE==4 || MODE==5) {
		ms=ms/2;       /* (mono/stereo) /2 */
		fn3=fun4(ms); }
	/*samplerate */
	if (MODE==2) {
		sr=sr/2;       /* SampleRate / 2 */ 
		fn4=fun3(sr);}
	if (MODE==3) {
		sr=sr*2;       /* SampleRate * 2 */ 
		fn4=fun3(sr);}
	if (MODE==4 || MODE==5 || MODE==6) {
		fn4=fun3(sr);}
	/*bytepersec */
	if (MODE==2 || MODE==4 || MODE==5) {
		bs=bs/2;      /* BYTESPERSEC / 2 */
		fn5=fun3(bs);}
	if (MODE==3) {
		bs=bs*2;      /* BYTESPERSEC * 2 */
		fn5=fun3(bs);}
	if (MODE==6) {
		fn5=fun3(bs);}
	/* BLOCKALIGN */
    if(MODE==2 || MODE==3 || MODE==6) {
		fn6=fun4(ba); }
	if(MODE==4 || MODE==5) {
		ba=ba/2;      /* blockalign / 2 */
		fn6=fun4(ba); }
	if (MODE!=1) {
    fn7=fun4(bps);
    putchar('d');
    putchar('a');
    putchar('t');
    putchar('a');
	fn8=fun3(sd); }
	
	if(MODE==2 || MODE==3 || MODE==1) {
		ch=getchar();
        while (ch != EOF) {
        	 count += 1;
             if(MODE==2 || MODE==3) {  putchar(ch); }
    	     ch=getchar(); 
		}
		if (count < sd) {
			fprintf(stderr, "Error! insufficient data\n");
    	    return 1; 
		}
        c=count+36;    /* 44-8=36*/
        if (c!=sf) {
        	fprintf(stderr, "Error! bad file size\n");
    	    return 1;	
		} 
    }
    if(bps==8) {      /*   if BITSPERSAMPLE = 8 and Mode=4 */
    	if(MODE==4) {
    		ch1=getchar();
    	    ch2=getchar();
    	    while (ch1 != EOF || ch2 != EOF) {
    	    	putchar(ch1);          /* putchar -->  left channel */
    	        ch1=getchar();
		        ch2=getchar(); }      
    	}
    	if(MODE==5) {
    		ch1=getchar();
    	    ch2=getchar();
    	    while (ch1 != EOF || ch2 != EOF) {
    	    	putchar(ch2);         /* putchar -->  right channel */
    	        ch1=getchar();
		        ch2=getchar(); }
	    }
		if(MODE==6) {
    	unsigned int md6;
    		ch=getchar();
    		while(ch != EOF) {
    			md6=ch/8;            /* divide all the bytes by 8 */
    			putchar(md6);
    			ch=getchar();}     
    	}
    }
    if (bps==16) {
    	if(MODE==4) {
    		ch1=getchar();
    	    ch2=getchar();
            ch3=getchar();
   	        ch4=getchar();
   	        while (ch1 !=EOF || ch2 != EOF ) {
   	        	putchar(ch1);
                putchar(ch2);
    	        ch1=getchar();
		        ch2=getchar();
    	        ch3=getchar();
		        ch4=getchar();
   	        }
    	}
    	if(MODE==5) {
    	    while ( ch3 !=EOF || ch4 != EOF ) {
    	        ch1=getchar();
		        ch2=getchar(); 
				ch3=getchar();
    	        ch4=getchar();
				md5=fun2(ch3, ch4);
    	        mo1=fun4(md5);}    
    	}
    
    }
    	if(MODE==6 && bps==16) {
    		ch1=getchar();
    		ch2=getchar();
    		while(ch1 !=EOF || ch2 != EOF) {
    			mo=fun2(ch1, ch2);
    			t1=mo & 0x8000;          /* for example : mo=(FFFF)hex(=(1111111111111111)binary)   t1=(1111111111111111) & (1000000000000000)   RESULT: (1000000000000000)binary */
    			t1=t1 >> 15;             /* NUMBER: (1000000000000000)binary   SHIFT DIRECTION: right(>>)   BITS TO SHIFT: 15  results: (1)bin  */
    			if(t1==1){               /* I want: Decimal number from signed 2's complement. If first bit is 1 --> number is negative */
    				mo=mo ^ 0xffff;      /* mo=(FFFF)hex      (FFFF) XOR (FFFF)  RESULT:(0000)hex : I reverse the bits*/
    			    mo=~mo;              /* 0000 ---> -1 */
    			    mo=mo/8;
    			    mo1=fun4(mo);
    			    ch1=getchar();
    			    ch2=getchar();
    			}
    			else {                   /*If first bit is not 1 --> number is positive */
    				mo=mo/8;
    				mo1=fun4(mo);
    			    ch1=getchar();
    			    ch2=getchar();
    			}
    		}
        }
	return 0; 
} 
