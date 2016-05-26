#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<ASU_tools.h>

/***********************************************************
 * This C function blur input signal array with gaussian function.
 *
 * double **p     ----  Input array pointer. ( nptsx*nptsy )
 * int    nptsx   ----  Number of traces in p.
 * int    nptsy   ----  Length of each traces of p.
 * double delta   ----  Sampling rate for each trace in p. ( in sec. )
 * double sigma   ----  Gaussian function parameter.
 * double gwidth  ----  Length of gaussian function. ( in sec. )
 *                      (gwidth/delta is npts of gaussian function)
 * double **ans   ----  Result ( nptsx*nptsy )
 *
 * Shule Yu
 * Jul 06 2014
 *
 * Key words: gaussian, blur, low pass filter.
***********************************************************/

void gaussblur_1d(double **p,int nptsx,int nptsy,double delta,double sigma,double gwidth,double **ans){

    int    count,count2,NPTS_Gauss;
    double *gauss,*tmp;

    NPTS_Gauss=1+2*(int)ceil(gwidth/2/delta);
    gauss=(double *)malloc(NPTS_Gauss*sizeof(double));
    tmp=(double *)malloc((nptsy+NPTS_Gauss-1)*sizeof(double));

    // Set up guassian function.
    gauss[NPTS_Gauss/2]=gaussian(0,sigma,0);
    for (count=0;count<NPTS_Gauss/2;count++){
        gauss[count]=gaussian(-(NPTS_Gauss/2-count)*delta,sigma,0);
        gauss[NPTS_Gauss-1-count]=gauss[count];
    }

    // Convolve signal with guassian function.
    // Truncate the smoothed array into original size.
	for (count=0;count<nptsx;count++){
		convolve(p[count],gauss,nptsy,NPTS_Gauss,tmp);
		for (count2=0;count2<nptsy;count2++){
			ans[count][count2]=tmp[count2+NPTS_Gauss/2];
		}
	}

    free(gauss);
    free(tmp);
    return ;
}
