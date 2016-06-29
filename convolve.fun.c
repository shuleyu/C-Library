#include<stdio.h>
#include<stdlib.h>
#include<ASU_tools.h>

/***********************************************************
 * This C function returns convolution result of two input
 * double array.
 *
 * double *x    ----  Array pointer x.
 * double *y    ----  Array pointer y.
 * int    nx    ----  Length of x.
 * int    ny    ----  Length of y.
 * double *ans  ----  Array pointer ans.
 *                    Pre-malloced. Length is nx+ny-1.
 *
 * Shule Yu
 * Jul 06 2014
 *
 * Key words: convolution.
***********************************************************/

void convolve(double *x,double *y,int nx,int ny,double *ans){

    if (nx<1||ny<1){
        printf("In %s: npts too small.\n",__func__);
        exit(1);
    }

    int count,count2,pmin,pmax;
    for (count=0;count<nx+ny-1;count++){
        pmin=(count>ny-1)?count-ny+1:0;
        pmax=(count<nx)?count+1:nx;
        ans[count]=0;
        for (count2=pmin;count2<pmax;count2++){
            ans[count]+=x[count2]*y[count-count2];
        }
    }

    return;
}
