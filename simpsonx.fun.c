#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<ASU_tools.h>

/***********************************************************
 * This C function returns integral value of f(x) using
 * Simpson's rule:
 *     number of intervals are self-decided;
 *     end loop condition: |ans_prev - ans| < res;
 *     double intervals at each loop.
 *
 * double (*fx)(double x)  ----  1-D variable function.
 * double lower_limit      ----  Integral lower bound.
 * double upper_limit      ----  Integral upper bound.
 * double res              ----  Accuracy. Tolerance.
 *
 * Shule Yu
 * Mar 20 2014
 *
 * Key words: simpson rule, integral
***********************************************************/

double simpsonx(double (*fx)(double),double lower_limit,double upper_limit,double res){

    if (lower_limit>upper_limit){
        printf("In %s: Boundary Error ...\n",__func__);
        exit(1);
    }

    int    intervalN,loop,count;
    double h,x,ans,ans_prev;

    loop=0;
    ans=0;
    ans_prev=0;
    intervalN=2;
    while ( loop<2 || fabs(ans_prev-ans) > res ){

        ans_prev=ans;
        ans=0;
        h=(upper_limit-lower_limit)/intervalN;

        // Sum up points over a weight pattern: 1 4 2 4 2 4 2 4 ..... 4 2 4 2 4 1.
        // First point.
        ans+=(*fx)(lower_limit);
        // inner point.
        x=lower_limit+h;
        for (count=1;count<intervalN;count++){
            ans+=(count%2+1)*2*(*fx)(x);
            x+=h;
        }
        // last point.
        ans+=(*fx)(upper_limit);

        ans*=(h/3);
        intervalN*=2;
        loop++;
    }

    return ans;
}
