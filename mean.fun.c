#include<ASU_tools.h>

// 2 functions:
// mean_d
// mean_f
// mean_i

/********************************************************
 * This C function returns the mean value of input array.
 *
 * float/double *p    ----  Array pointer.
 * int          npts  ----  Array npts.
 *
 * Shule Yu
 * Apr 20 2015
 *
 * Key words: mean, summation.
***********************************************************/

double mean_d(double *p, int npts){

    if (npts==0){
        return 0.0/0.0;
    }

    double m;

    m=sum_d(p,npts);
    m=1.0*m/npts;

    return m;
}

float mean_f(float *p, int npts){

    if (npts==0){
        return 0.0/0.0;
    }

    float m;

    m=sum_f(p,npts);
    m=1.0*m/npts;

    return m;
}

double mean_i(int *p, int npts){

    if (npts==0){
        return 0.0/0.0;
    }

    double m;

    m=sum_i(p,npts);
    m=1.0*m/npts;

    return m;
}
