#include<stdio.h>
#include<math.h>
#include<ASU_tools.h>

/**************************************************************
 * This C function find the max(abs(amp)) position for a given
 * input array.
 *
 * double *p  ----  Array pointer.
 * int npts   ----  Array npts.
 * int *Peak  ----  Input: rough peak position.
 *                  Output: correct peak position.
 * int WB     ----  Window begin, relative to RoughPeak.
 * int WL     ----  Window length.
 *
 * Shule Yu
 * Apr 05 2016
 *
 * Key words: peak position
***********************************************************/

void findpeak(double *p, int npts, int *Peak, int WB, int WL){

    if (WL <=0 || *Peak+WB>npts-1 || *Peak+WB<0 ){
        printf("In %s: Windowing error ...\n",__func__);
        return;
    }

	int End=*Peak+WB+WL-1;
	if ( End>npts-1 ){
		End=npts-1;
	}

    int count;
	double AMP=fabs(p[*Peak]);
    for (count=*Peak+WB;count<=End;count++){
        if (AMP<fabs(p[count])){
            AMP=fabs(p[count]);
			*Peak=count;
        }
    }

    return;
}
