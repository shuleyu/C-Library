// Done. (Use C++ standard library to binary search.)

#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<ASU_tools.h>

/***********************************************************
 * This C function returns search result using binary search
 * algorithm for f(x). f(x) should be monotonous.
 *
 * double (*f)(double)  ----  Function pionter.
 * double x1            ----  Lower search limit.
 * double x2            ----  Upper search limit.
 * double keyval        ----  Target value.
 * doulbe tol           ----  Acurracy tolerance.
 *
 * Shule Yu
 * May 13 2014
 *
 * Key words: binary search
 *
 * Reference:
 *     http://en.wikipedia.org/wiki/Binary_search_algorithm
***********************************************************/

double binary_search(double (*f)(double),double x1, double x2, double keyval,double tol){

    if ( x1 > x2){
        printf("In %s: Boundary error !\n",__func__);
        exit(1);
    }

    double A,B,C,midpoint;

    midpoint=(x1+x2)/2.0;

    A=(*f)(x1);
    B=(*f)(x2);
    C=(*f)(midpoint);

    if ( ( fabs(x1-x2) > tol ) && ( ( C > keyval && A < B ) || ( C < keyval && A > B ) ) ){
        return binary_search((*f),x1,midpoint,keyval,tol);
    }
    else if ( ( fabs(x1-x2) > tol ) && ( ( C > keyval && A > B ) || ( C < keyval && A < B ) ) ){
        return binary_search((*f),midpoint,x2,keyval,tol);
    }
    else{
        return midpoint;
    }
}
