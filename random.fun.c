// Done. (Use C++ standard library to generate random numbers.)
// See Bootstrap.hpp in the C++ library.

#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>
#include<unistd.h>
#include<ASU_tools.h>

// 3 functions
// random_num
// random_int
// random_gaussian

/***********************************************************
 * This C function returns an array of npts random numbers.
 *
 * (for random_num:)
 * Doubles, range: 0 ~ 1.
 *
 * (for random_int:)
 * Integers, range : min ~ max (min<=max).
 *
 * (for random_gaussian:)
 * Doubles, have the normal distribution N ( mu, sigma ).
 * Using the Box-Muller transform.
 *
 * int   *p    ----  Output array pointer.
 * int   npts  ----  Array npts.
 *
 * (for random_int:)
 * int   max   ----  Random number minimum value.
 * int   max   ----  Random number maximum value.
 *
 * (for random_gaussian:)
 * double mu     ----  Expectation.
 * double sigma  ----  Standard deviation.
 *
 *
 * Shule Yu
 * Oct 17 2014
 *
 * Reference: http://en.wikipedia.org/wiki/Box–Muller_transform
 *
 * Key words: random.
***********************************************************/

void random_num(double *p,int npts){

    srand(time(NULL));

    long x;
    unsigned long num_bins,num_rand,bin_size,defect;
    int  count,max;
    max=1000000;

    num_bins=(unsigned long)max+1;
    num_rand=(unsigned long)RAND_MAX+1;
    bin_size=num_rand/num_bins;
    defect=num_rand%bin_size;

    for (count=0;count<npts;count++){
        while (num_rand-defect<=(unsigned long)(x=rand()));
        p[count]=1.0*(1+(int)x/bin_size)/max;
    }

    normalized(p,npts);

    sleep(1);
    return;
}

void random_int(int min, int max,int *p,int npts) {

	if (min>max){
		printf("In %s: Range error ...\n",__func__);
		return;
	}

	int count;

	if (min==max){
		for (count=0;count<npts;count++){
			p[count]=min;
		}
		sleep(1);
		return;
	}

    max-=1;
    srand(time(NULL));

    long x;
    unsigned long num_bins,num_rand,bin_size,defect;

    num_bins=(unsigned long)max+1;
    num_rand=(unsigned long)RAND_MAX+1;
    bin_size=num_rand/num_bins;
    defect=num_rand%bin_size;

    for (count=0;count<npts;count++){
        while (num_rand-defect<=(unsigned long)(x=rand()) || 1+(int)x/bin_size < min);
        p[count]=1+(int)x/bin_size;
    }

	sleep(1);
    return;
}

void random_gaussian(double *p,int npts,double mu,double sigma){

    int    count;
    double *p1,eps;

    eps=1e-15;

    p1=(double *)malloc(2*npts*sizeof(double));
    random_num(p1,2*npts);

    for (count=0;count<2*npts;count++){
        if (p1[count]<eps){
            p1[count]=eps;
        }
    }

    for (count=0;count<npts;count++){
        p[count]=sqrt(-2*log(p1[count]))*cos(2*M_PI*p1[count+npts]);
        p[count]=sigma*p[count]+mu;
    }

    free(p1);

    return;
}
