// Done.

#include<stdio.h>
#include<ASU_tools.h>

/***********************************************************
 * This C function make division between two complex number:
 * a+ib and c+id, let the result be e+if:
 *
 *        a+bi
 * e+fi= ------
 *        c+di
 *
 * double a   ----  a.
 * double b   ----  b.
 * double c   ----  c.
 * double d   ----  d.
 * double *e  ----  e.
 * double *f  ----  f.
 *
 * Shule Yu
 * Jul 13 2014
 *
 * Key words: complex, divide, division.
***********************************************************/

void complex_divide(double a, double b, double c,double d,double *e, double *f){

    if (c==0 && d==0){
        printf("In %s: Divided by zero !\n",__func__);
		(*e)=0.0/0.0;
		(*f)=0.0/0.0;
        return;
    }
	
    (*e)=(a*c+b*d)/(c*c+d*d);
    (*f)=(b*c-a*d)/(c*c+d*d);
    return;
}
