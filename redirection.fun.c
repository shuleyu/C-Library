#include<stdio.h>
#include<ASU_tools.h>

// 3 functions
// redirect_i 
// redirect_f 
// redirect_d 

/**************************************************************
 * This C function store the redirected input 2D grid (as an
 * array)into a pre-allocated array.
 *
 * int/float/double *p   ----  Original 2D grid. (1 by nx*ny)
 * int              nx   ----  x size.
 * int              ny   ----  y size.
 * int/float/double *pp  ----  Transposed 2D grid. (1 by nx*ny)
 *
 * Shule Yu
 * Jan 22 2016
 *
 * Key words: redirection.
**************************************************************/

void redirect_i(int *p, int nx, int ny, int *pp){

	int Cnt,Cnt2,Cnt3=0;
	for (Cnt=0;Cnt<ny;Cnt++){
		for (Cnt2=0;Cnt2<nx;Cnt2++){
			pp[Cnt3]=p[Cnt+Cnt2*ny];
			Cnt3++;
		}
	}

	return;
}

void redirect_f(float *p, int nx, int ny, float *pp){

	int Cnt,Cnt2,Cnt3=0;
	for (Cnt=0;Cnt<ny;Cnt++){
		for (Cnt2=0;Cnt2<nx;Cnt2++){
			pp[Cnt3]=p[Cnt+Cnt2*ny];
			Cnt3++;
		}
	}

	return;
}

void redirect_d(double *p, int nx, int ny, double *pp){

	int Cnt,Cnt2,Cnt3=0;
	for (Cnt=0;Cnt<ny;Cnt++){
		for (Cnt2=0;Cnt2<nx;Cnt2++){
			pp[Cnt3]=p[Cnt+Cnt2*ny];
			Cnt3++;
		}
	}

	return;
}
