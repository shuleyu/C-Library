#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<ASU_tools.h>

/***********************************************************
 * This C function returns the legendre polynomial of input
 * parameters.
 *
 * int    l  ----  Lower number.
 * int    m  ----  Upper number.
 * double x  ----  cos \theta.
 *
 * Return definition is:
 *
 * P_{l}^{m}(x) = \dfrac{1}{2^l l!} (1-x^2)^{m/2} \dfrac{\dif ^{l+m}}{\dif x^{l+m}} (x^2-1)^l
 * x \in [ -1 , 1 ].
 * m = -l , -l+1, ..., 0, ... , l-1, l.
 * l >= 0.
 *
 * Shule Yu
 * Mar 10 2015
 *
 * Key words: legendre; polynomial
***********************************************************/

double legendre(int l, int m, double x){

    if ( l < 0 || m < -l || m > l || x < -1 || x > 1 ){
        printf("In %s: input error...\n",__func__);
        exit(1);
    }

    int    count,count2;
    double tmp,ans;

    ans=0;
    for (count=(l+m+1)/2;count<=l;count++){
        tmp=1;
        for (count2=2*count-l-m+1;count2<=2*count;count2++){
            tmp*=count2;
        }
        ans+=combination(l,count)*pow(-1,l-count)*tmp*pow(x,2*count-l-m);
    }

    ans*=pow(1-x*x,1.0*m/2);

    for (count=1;count<=l;count++){
        ans/=(2*count);
    }

    return ans*pow(-1,m);
}
