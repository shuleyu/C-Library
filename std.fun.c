#include<math.h>
#include<ASU_tools.h>

// 4 functions:
// std_f
// std_d
// std_i
// std_err
// std_errd

/***********************************************************
 * This C function returns unbiased estimation of standard
 * deviation for input array. The formula is :
 *
 * s=\sqrt{\dfrac{1}{NPTS-1}*\sum_{i=1}^NPTS (x_i-\bar{x})^2}
 *
 * (for std_err:)
 * \dfrac{s}{\sqrt{npts}}
 *
 * float/double *p    ----  Array pointer.
 * int          npts  ----  Array npts.
 *
 * Shule Yu
 * Apr 15 2014
 *
 * Note: when npts<=1, we return 0.
 *
 * Key words: standard deviation, unbiased.
 *
 * Reference:
 *     http://en.wikipedia.org/wiki/Unbiased_estimation_of_standard_deviation
 *     http://en.wikipedia.org/wiki/Standard_error
***********************************************************/

double std_f(float *p, int npts){

    if (npts<=1){
        return 0;
    }

    int    count;
    double ans,avrx;

    // Calculate x average.
    avrx=mean_f(p,npts);

    // Calculate summation.
    ans=0;
    for (count=0;count<npts;count++){
        ans+=pow((p[count]-avrx),2);
    }

    // Return standard deviation.
    return sqrt(ans/(npts-1));
}

double std_d(double *p, int npts){

    if (npts<=1){
        return 0;
    }

    int    count;
    double ans,avrx;

    // Calculate x average.
    avrx=mean_d(p,npts);

    // Calculate summation.
    ans=0;
    for (count=0;count<npts;count++){
        ans+=pow((p[count]-avrx),2);
    }

    // Return standard deviation.
    return sqrt(ans/(npts-1));
}

double std_i(int *p, int npts){

    if (npts<=1){
        return 0;
    }

    int    count;
    double ans,avrx;

    // Calculate x average.
    avrx=mean_i(p,npts);

    // Calculate summation.
    ans=0;
    for (count=0;count<npts;count++){
        ans+=pow((p[count]-avrx),2);
    }

    // Return standard deviation.
    return sqrt(ans/(npts-1));
}


double std_err(float *p, int npts){

    if (npts<=1){
        return 0;
    }

	return std_f(p,npts)/sqrt(npts);
}

double std_errd(double *p, int npts){

    if (npts<=1){
        return 0;
    }

	return std_d(p,npts)/sqrt(npts);
}
