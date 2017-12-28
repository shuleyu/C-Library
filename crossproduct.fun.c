// Done.

#include<stdio.h>
#include<math.h>
#include<ASU_tools.h>

// 2 functions:
// crossproduct
// crossproduct_2d

/**************************************************************
 * This C function take the cross product of
 * (x1,y1,z1) and (x2,y2,z2).
 *
 * double x1   ----  x value of ponits 1.
 * double y1   ----  y value of ponits 1.
 * double z1   ----  z value of ponits 1.
 * double x2   ----  x value of ponits 2.
 * double y2   ----  y value of ponits 2.
 * double z2   ----  z value of ponits 2.
 * double *x3  ----  x value of result.
 * double *y3  ----  y value of result.
 * double *z3  ----  z value of result.
 *
 * (for crossproduct_2d:)
 * Take the cross product of two vectors in plane (z=0).
 * Return > 0 : pointing to positive z direction.
 * Return < 0 : pointing to negative z direction.
 *
 * double x1   ----  x value of ponits 1.
 * double y1   ----  y value of ponits 1.
 * double x2   ----  x value of ponits 2.
 * double y2   ----  y value of ponits 2.
 *
 * Shule Yu
 * Dec 09 2015
 *
 * Key words: cross product.
****************************************************************/

inline void crossproduct(double x1, double y1, double z1, double x2, double y2, double z2, double *x3, double *y3, double *z3){
	(*x3)=(y1*z2-y2*z1);
	(*y3)=(z1*x2-z2*x1);
	(*z3)=(x1*y2-x2*y1);
	return;
}

inline double crossproduct_2d(double x1, double y1, double x2, double y2){
	return (x1*y2-x2*y1);
}
