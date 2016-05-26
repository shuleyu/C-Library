#include<stdio.h>
#include<ASU_tools.h>

// 3 functions
// print_2d_array_f

/**************************************************************
 * This C function print a 1D array input as a 2D array.
 * p[0] is at lower left corner.
 * Positive direction is right (x) and up (y).
 *
 * int/float/double *p   ----  Original 2D array. (1 by nx*ny)
 * int              nx   ----  x size.
 * int              ny   ----  y size.
 *
 * Shule Yu
 * Jan 27 2016
 *
 * Key words: array, I/O
**************************************************************/

void print_2d_array_f(float *p, int nx, int ny){

	int Cnt,Cnt2=0;
	for (Cnt=ny-1;Cnt>=0;Cnt--){
		for (Cnt2=0;Cnt2<nx;Cnt2++){
			printf("%.2f\t",p[Cnt2*ny+Cnt]);
		}
		printf("\n");
	}

	return;
}
