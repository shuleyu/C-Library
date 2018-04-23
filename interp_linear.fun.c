#include<stdio.h>
#include<stdlib.h>
#include<ASU_tools.h>

// 2 functions:
// interp2_linear
// interp3_linear

/**************************************************************
 *
 * (for interp2_linear:)
 * This C function use bilinear interpolation algorithm to
 * interpolate within a unit square, using the value at four
 * corners.
 *
 * The input array is :
 *
 * p[0]=f(0,0)
 * p[1]=f(1,0)
 * p[2]=f(0,1)
 * p[3]=f(1,1)
 *
 * new position: (dx,dy), output f(dx,dy).
 *
 * double *p    ----  Input square value, length is 4.
 * double *dx   ----  New position dx.
 * double *dy   ----  New position dy.
 *
 * (for interp3_linear:)
 * This C function use trilinear interpolation algorithm to
 * interpolate within a unit cubic, using the value at eight
 * corners.
 *
 * The input array is:
 *
 * p[0]=f(0,0,0)
 * p[1]=f(1,0,0)
 * p[2]=f(0,1,0)
 * p[3]=f(1,1,0)
 * p[4]=f(0,0,1)
 * p[5]=f(1,0,1)
 * p[6]=f(0,1,1)
 * p[7]=f(1,1,1)
 *
 * new position: (dx,dy,dz), output f(dx,dy,dz).
 *
 * double *p    ----  Input cubic value, length is 8.
 * double *dx   ----  New position dx.
 * double *dy   ----  New position dy.
 * double *dz   ----  New position dz.
 *
 *
 * Shule Yu
 * May 24 2014
 *
 * Reference:
 *     http://en.wikipedia.org/wiki/Bilinear_interpolation
 *     http://en.wikipedia.org/wiki/Trilinear_interpolation
 * Key words: interpolation, linear.
**************************************************************/

double interp2_linear(double *p,double dx,double dy){

    if ( dx<0 || dx>1 || dy<0 || dy>1 ){
        printf("In %s: Point outside of square ...\n",__func__);
        exit(1);
    }

    double c0,c1;

    // Step1. Calculate value at ( dx , 0 ) ( dx , 1 ).
    c0=p[0]*(1-dx)+p[1]*dx;
    c1=p[2]*(1-dx)+p[3]*dx;

    // Step2. Calculate value at ( dx, dy ).
    return c0*(1-dy)+c1*dy;
}

double interp3_linear(double *p,double dx,double dy,double dz){

    if ( dx<0 || dx>1 || dy<0 || dy>1 || dz<0 || dz>1 ){
        printf("In %s: Point outside of cubic ...\n",__func__);
        printf("       dx,dy,dx=%.2lf,%.2lf,%.2lf\n",dx,dy,dz);
        double Sum=0;
        for (int i=0;i<8;i++)
            Sum+=p[i];
        return Sum/8;
    }

    double c00,c10,c01,c11,c0,c1;

    // Step1. Calculate value at ( dx , 0 , 0 ) ( dx , 1 , 0 ) ( dx , 0 , 1 ) ( dx , 1 , 1 ).
    c00=p[0]*(1-dx)+p[1]*dx;
    c10=p[2]*(1-dx)+p[3]*dx;
    c01=p[4]*(1-dx)+p[5]*dx;
    c11=p[6]*(1-dx)+p[7]*dx;

    // Step2. Calculate value at ( dx , dy , 0 ) ( dx , dy , 1 ).
    c0=c00*(1-dy)+c10*dy;
    c1=c01*(1-dy)+c11*dy;

    // Step3. Calculate value at ( dx, dy, dz ).
    return c0*(1-dz)+c1*dz;
}
