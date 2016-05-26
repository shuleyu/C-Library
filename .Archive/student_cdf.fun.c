#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<ASU_tools.h>

/*******************************************************************
 * This C function returns the CDF of student's t distribution.
 * Defined as:
 *
 * P_n(X<=x) =  \int_{-\infty}*{x} tpdf(x,n) \dif x
 *
 * double x  ----  Random variable.
 * int    n  ----  number of degrees of freedom.
 *
 * Note: we use simpson rule to do the integra from 0 to x.
 *
 * Shule Yu
 * Apr 20 2015
 *
 * Key words: sutdent ; statistics 
*******************************************************************/

double student_cdf(double xx, int n){

    if ( n <= 0 ){
        printf("In %s: degree of freedom should > 0 ...\n",__func__);
        exit(1);
    }

    if (xx==0){
        return 0.5;
    }

    int    intervalN,loop,count;
    double x,h,ans,ans_prev,upper_limit,lower_limit;
    
    if (xx<0){
        upper_limit=-xx;
    }
    else{
        upper_limit=xx;
    }
    lower_limit=0;


    loop=0;
    ans=0;
    ans_prev=0;
    intervalN=2;
    while ( loop<2 || fabs(ans_prev-ans) > 1e-9 ){

        ans_prev=ans;
        ans=0;
        h=(upper_limit-lower_limit)/intervalN;

        // Sum up points over a weight pattern: 1 4 2 4 2 4 2 4 ..... 4 2 4 2 4 1.
        // First point.
        ans+=student_pdf(lower_limit,n);
        // inner point.
        x=lower_limit+h;
        for (count=1;count<intervalN;count++){
            ans+=(count%2+1)*2*student_pdf(x,n);
            x+=h;
        }
        // last point.
        ans+=student_pdf(upper_limit,n);

        ans*=(h/3);
        intervalN*=2;
        loop++;
    }

    if (xx<0){
        return 0.5-ans;
    }
    else{
        return 0.5+ans;
    }
}
