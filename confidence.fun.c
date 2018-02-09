#include<math.h>
#include<gsl/gsl_cdf.h>
#include<ASU_tools.h>

/***************************************************************
 * This C function returns the 95% confidence boundary of input
 * measurements, assuming the error is normal distribution.
 *
 * double *p     ----  Array pointer.
 * int    npts   ----  Array npts.
 * double *r     ----  range. @ student m+-t_{npts-1},0.975*sigma/sqrt{n})
 * double level  ----  confidence level. ( e.g. 95% use 0.95 )
 *
 * Shule Yu
 * Apr 20 2015
 *
 * Key words: confidence level.
***********************************************************/

void confidence(double *p, int npts, double *r,double level){

    if (npts<=1){
        (*r)=0;
        return;
    }

    double s=std_d(p,npts);

    (*r)=gsl_cdf_tdist_Pinv(1-(1-level)/2,npts-1)*s/sqrt(npts);

    return;
}
