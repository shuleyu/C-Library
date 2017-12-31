// Done.

#include<math.h>
#include<ASU_tools.h>

/***********************************************************
 * This C function returns the value of one mollifier function
 * with given width.
 *
 * The formula for the mollifier function is:
 *
 * f(x)=1/delta*g(x/delta).
 *
 * while,
 *
 * g(x)=e^{\dfrac{-1}{1-x^2}} ( namely f(x) with delta=1 )
 *
 * double x      ----  x.
 * double delta  ----  delta.
 *
 * Shule Yu
 * Sept 22 2014
 *
 * Key words: mollifier
***********************************************************/

double mollifier(double x,double delta){
    if (fabs(x)>=delta){
        return 0;
    }
    else{
        return exp(-1/(1-pow((x/delta),2)))/delta;
    }
}
