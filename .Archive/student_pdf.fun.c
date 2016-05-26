#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<ASU_tools.h>

/*******************************************************************
 * This C function returns the PDF of student's t distribution.
 * Defined as:
 *
 * f(x,n)=\dfrac{1}{\sqrt{n\pi}}\dfrac{\Gamma((n+1)/2)}{\Gamma(n/2)}(1+x^2/n)^(-(n+1)/2)
 *
 * double x  ----  Random variable.
 * int    n  ----  number of degrees of freedom.
 *
 * Shule Yu
 * Apr 20 2015
 *
 * Key words: sutdent ; statistics 
*******************************************************************/

double student_pdf(double x, int n){

    if ( n <= 0 ){
        printf("In %s: degree of freedom should > 0 ...\n",__func__);
        exit(1);
    }

    double tmp;

    tmp=1+pow(x,2)/n;

    return exp( lgamma((n+1)/2.0) - lgamma((n)/2.0) ) * pow(tmp,-(n+1)/2.0) /sqrt(n*M_PI);
}
