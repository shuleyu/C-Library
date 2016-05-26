#include<stdio.h>
#include<stdlib.h>
#include<ASU_tools.h>

/***********************************************************
 * This C function returns the value of a ramp function
 * defined by given parameters:
 *
 * f(x) =   0   x<c1;
 *          1   x>c2;
 *          linear rise from 0 to 1 while x from c1 to c2.
 *
 * double x   ----  x.
 * double c1  ----  left boundary.
 * double c2  ----  right boundary.
 *
 * Shule Yu
 * Oct 08 2014
 *
 * Key words: ramp
***********************************************************/

double ramp_function(double x, double c1, double c2){

    if (c1>c2){
        printf("In %s: c1 > c2 ...",__func__);
        exit(1);
    }
	else if (c1==c2){
		if (x>c2){
			return 1.0;
		}
		else{
			return 0.0;
		}
	}

	else{
		if (x>=c2){
			return 1.0;
		}
		if (x<=c1){
			return 0.0;
		}
		return (x-c1)/(c2-c1);
	}
}
