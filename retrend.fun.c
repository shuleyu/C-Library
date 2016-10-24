#include<stdio.h>
#include<math.h>
#include<ASU_tools.h>

// 2 functions
// retrend
// retrendd
// linear_fitting

/***********************************************************
 * This C function remove linear trend of input signal.
 * By "signal", we assume it's evenly sampled.
 *
 * First apply square least fitting to the signal, then
 * remove the linear trend.
 *
 * double       xbegin  ----  Time of the first point.
 * float/double *data   ----  Amplitude array pointer.
 * int          npts    ----  Length of the array.
 * double       delta   ----  Sampling rates of the signal.
 *
 * (for linear_fitting)
 *
 * double       *x    ----  X_i
 * double *y          ----  Y_i
 * int    npts        ----  Length of the array.
 * double *slope      ----  \hat{b}
 * double *intercept  ----  \hat{a}
 *
 * least square solution of a,b:
 *
 * Y_i = b * X_i + a
 *
 * Shule Yu
 * Feb 19 2014
 *
 * Note: Original data destroyed.
 * Key words: square least fitting, remove trend.
 *
 * Reference:
 *     http://en.wikipedia.org/wiki/Simple_linear_regression
***********************************************************/

void retrend(double xbegin,float *data,int npts,double delta){

    int    count;
    double slope,intercept,avx,sumx2,sumy,sumxy;

    avx=(npts-1)/2.0*delta+xbegin;
    sumx2=0;
    sumy=0;
    sumxy=0;
    for (count=0;count<npts;count++){
        sumx2+=pow(xbegin+delta*count,2);
        sumy+=data[count];
        sumxy+=data[count]*(xbegin+delta*count);
    }

    // calculate the fitting line's slope and intercept value.
    slope=(sumxy-sumy*avx)/(sumx2-npts*avx*avx);
    intercept=sumy/npts-slope*avx;

    // remove the trend (and avx) for input data points.
    for (count=0;count<npts;count++){
        data[count]-=(intercept+(xbegin+count*delta)*slope);
    }

    return;
}

void retrendd(double xbegin,double *data,int npts,double delta){

    int    count;
    double slope,intercept,avx,sumx2,sumy,sumxy;

    avx=(npts-1)/2.0*delta+xbegin;
    sumx2=0;
    sumy=0;
    sumxy=0;
    for (count=0;count<npts;count++){
        sumx2+=pow(xbegin+delta*count,2);
        sumy+=data[count];
        sumxy+=data[count]*(xbegin+delta*count);
    }

    // calculate the fitting line's slope and intercept value.
    slope=(sumxy-sumy*avx)/(sumx2-npts*avx*avx);
    intercept=sumy/npts-slope*avx;

    // remove the trend (and avx) for input data points.
    for (count=0;count<npts;count++){
        data[count]-=(intercept+(xbegin+count*delta)*slope);
    }

    return;
}

void linear_fitting(double *x,double *y,int npts,double *slope,double *intcpt){

	if (npts<=1){
        printf("In %s: NPTS too small ...\n",__func__);
		return;
	}

    int    count;
    double avx,sumx2,sumy,sumxy;

    avx=0;
    for (count=0;count<npts;count++){
		avx+=x[count];
	}
	avx/=npts;

    sumx2=0;
    sumy=0;
    sumxy=0;
    for (count=0;count<npts;count++){
        sumx2+=pow(x[count],2);
        sumy+=y[count];
        sumxy+=y[count]*x[count];
    }

    // calculate the fitting line's slope and intercept value.
    *slope=(sumxy-sumy*avx)/(sumx2-npts*pow(avx,2));
    *intcpt=sumy/npts-(*slope)*avx;

	return;
}
