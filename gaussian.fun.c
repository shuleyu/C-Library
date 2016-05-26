#include<math.h>
#include<ASU_tools.h>

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
