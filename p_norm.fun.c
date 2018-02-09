#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<ASU_tools.h>

// 2 functions
// p_norm
// p_norm_err

/***********************************************************
 * This C function returns the vector p-norm of input vector.
 *
 * (for p_norm_err:)
 * Returns the p-norm difference between two input vectors 
 * defined as:
 *
 *  | x - y | _ p
 * ----------------
 *    | y | _ p
 *
 * double *x    ----  Array pointer.
 * int    npts  ----  Array npts.
 * double p     ----  p-norm.
 *
 * (for p_norm_err:)
 *
 * double *y    ----  Target Array pointer.
 *
 * Shule Yu
 * Nov 02 2014
 *
 * Key words: l^2 p-norm.
***********************************************************/

double p_norm(double *x, int npts, double p){

    if (npts<=0){
        printf("In %s: NPTS too small ...\n",__func__);
        exit(1);
    }

    int    count;
    double tmpsum;

    tmpsum=0;
    for (count=0;count<npts;count++){
        tmpsum+=pow(fabs(x[count]),p);
    }
    return pow(tmpsum,1.0/p);
}

double p_norm_err(double *x, double *y,int npts, double p){

    if (npts<=0){
        printf("In %s: NPTS too small ...\n",__func__);
        exit(1);
    }

    int    count;
    double tmpsum;

    tmpsum=0;
    for (count=0;count<npts;count++){
        tmpsum+=pow(fabs(x[count]-y[count]),p);
    }
    return pow(tmpsum,1.0/p)/p_norm(y,npts,p);
}
