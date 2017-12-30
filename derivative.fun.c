// Done.

#include<stdio.h>
#include<ASU_tools.h>

// 2 functions:
// derivative
// derivative_f

/***********************************************************
 * This C function takes the cummulative difference of an
 * input array.
 *
 * float/double *p    ----  Array pointer.
 * int          npts  ----  Array npts.
 * float/double *pp   ----  Output array. (1*npts)
 *
 *
 * Shule Yu
 * Dec 11 2016
 *
 * Key words: derivative.
 *
 * Note: pp[npts-1] is set to the value of pp[npts-2] for 
 * convenience.
***********************************************************/

void derivative(double *p, int npts, double *pp){

    if (npts<=0){
        printf("In %s: NPTS too small ...\n",__func__);
        return;
    }

    for (int count=0;count<npts-1;count++){
		pp[count]=p[count+1]-p[count];
    }
	pp[npts-1]=pp[npts-2];

    return;
}

void derivative_f(float *p, int npts, double *pp){

    if (npts<=0){
        printf("In %s: NPTS too small ...\n",__func__);
        return;
    }

    for (int count=0;count<npts-1;count++){
		pp[count]=p[count+1]-p[count];
    }
	pp[npts-1]=pp[npts-2];

    return;
}
