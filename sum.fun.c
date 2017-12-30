// Done.
// Ues standard libaray funciton accumulate:
// Sum=accumulate(A.begin(),A.end(),0.0);

#include<stdio.h>
#include<ASU_tools.h>

// 3 functions
// sum_d
// sum_i
// sum_f

/***********************************************************
 * This C function returns the summation of input array.
 *
 * int/float/double *p    ----  Array pointer.
 * int              npts  ----  Array npts.
 *
 * Shule Yu
 * Nov 04 2015
 *
 * Key words: summation
***********************************************************/

double sum_d(double *p, int npts){
	
	int    Cnt;
	double Sum=0;

	for (Cnt=0;Cnt<npts;Cnt++){
		Sum+=p[Cnt];
	}

	return Sum;
}

int sum_i(int *p, int npts){
	
	int    Cnt,Sum=0;

	for (Cnt=0;Cnt<npts;Cnt++){
		Sum+=p[Cnt];
	}

	return Sum;
}

float sum_f(float *p, int npts){
	
	int   Cnt;
	float Sum=0;

	for (Cnt=0;Cnt<npts;Cnt++){
		Sum+=p[Cnt];
	}

	return Sum;
}
