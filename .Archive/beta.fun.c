#include<math.h>
#include<ASU_tools.h>

/***********************************************************
 * This C function returns Beta function at certain tolerance.
 *
 * Formula:
 *
 * B(m,n) = \int_{0}^{1} t^(m-1) (1-t)^{n-1} \dif t
 *
 * double m    ----  M.
 * double n    ----  N.
 * double tol  ----  Toloerance.
 *
 * Shule Yu
 * Jul 10 2014
 *
 * Key words: beta function
 *
 * Reference:
 *     http://en.wikipedia.org/wiki/Beta_function
***********************************************************/

double fx(double x,double m,double n){
    return pow(x,m-1)*pow((1-x),n-1);
}

// Use simpson rule on fx's 0 ~ 1 integral.
double beta(double m,double n,double tol){

    double lower_limit,upper_limit,h,x;
    double ans,ans_prev;
    int    intervalN,loop,count;

    lower_limit=0;
    upper_limit=1;

    loop=0;
    ans=0;
    ans_prev=0;
    intervalN=2;
    while ( loop<2 || fabs(ans_prev-ans) > tol ){

        ans_prev=ans;
        ans=0;
        h=(upper_limit-lower_limit)/intervalN;

        // Sum up points over a weight pattern: 1 4 2 4 2 4 2 4 ..... 4 2 4 2 4 1.
        // First point.
        ans+=fx(lower_limit,m,n);
        // Inner point.
        x=lower_limit+h;
        for (count=1;count<intervalN;count++){
            ans+=(count%2+1)*2*fx(x,m,n);
            x+=h;
        }
        // Last point.
        ans+=fx(upper_limit,m,n);

        ans*=(h/3);
        intervalN*=2;
        loop++;
    }

    return ans;
}
