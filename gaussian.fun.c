#include<math.h>
#include<ASU_tools.h>

// 2 functions.
// gaussian
// gaussianfun

/***********************************************************
 * This C function returns the value of gaussian function.
 * Integral from -\infty to \infty is 1.
 * Namely the PDF of normally distributed, definition is:
 *
 * f(x)=\dfrac{1}{\sigma\sqrt{2\pi}} e^{-\dfrac{(x-\mu)^2}{2\sigma^2}}
 *
 * double x      ----  x.
 * double sigma  ----  standard deviation, sigma.
 * double mu     ----  average value, mu.
 *
 * for gaussianfun:
 * signal is centered at the peak.
 *
 * double *p     ----  output signal, pre-mallocated space. (1*npts)
 * int    npts   ----  signal length.
 * double delta  ----  sampling rate. 
 * double sigma  ----  standard deviation, sigma.
 *
 * Shule Yu
 * Jul 06 2014
 *
 * Key words: gaussian function.
***********************************************************/

double gaussian(double x,double sigma,double mu){
	if (sigma<0){
		return 1;
	}
    if (sigma==0){
        if (x==0){
            return 1;
        }
        else{
            return 0;
        }
    }
    else{
        return exp(-0.5*pow((x-mu)/sigma,2))/sigma/sqrt(2*M_PI);
    }
}

void gaussianfun(double *p,int npts,double delta,double sigma){

	int count;

    p[npts/2]=gaussian(0,sigma,0);

	if (sigma<0){
		for (count=0;count<npts;count++){
			p[count]=0;
		}
		return;
	}

    for (count=0;count<npts/2;count++){
        p[count]=gaussian(-(npts/2-count)*delta,sigma,0);
        p[npts-1-count]=p[count];
    }
	return;
}
