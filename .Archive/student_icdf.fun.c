#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<ASU_tools.h>

/*******************************************************************
 * This C function returns the inverse of CDF of student's t 
 * distribution.
 * 
 * Defined as P_n(X<=x) = a.
 *
 * double a  ----  probability value. ( 0 <= a <= 1 )
 * int    n  ----  number of degrees of freedom.
 *
 * Note: we use simpson rule to do the integra from 0 to x.
 *
 * Shule Yu
 * Apr 20 2015
 *
 * Key words: sutdent ; statistics 
*******************************************************************/

double binary_search_student(double x1, double x2, double keyval,double tol,int n){

    double A,B,C,midpoint;

    midpoint=(x1+x2)/2.0;

    A=student_cdf(x1,n);
    B=student_cdf(x2,n);
    C=student_cdf(midpoint,n);

    if ( ( fabs(x1-x2) > tol ) && ( ( C > keyval && A < B ) || ( C < keyval && A > B ) ) ){
        return binary_search_student(x1,midpoint,keyval,tol,n);
    }
    else if ( ( fabs(x1-x2) > tol ) && ( ( C > keyval && A > B ) || ( C < keyval && A < B ) ) ){
        return binary_search_student(midpoint,x2,keyval,tol,n);
    }
    else{
        return midpoint;
    }
}

double student_icdf(double a, int n){

    if ( n <= 0 ){
        printf("In %s: degree of freedom should > 0 ...\n",__func__);
        exit(1);
    }

    if (a==1){
        return 1/0.0;
    }
    if (a==0){
        return 0.0;
    }

    return binary_search_student(-1e3,1e3,a,1e-10,n);

}
