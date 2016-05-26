#include<stdio.h>
#include<stdlib.h>
#include<ASU_tools.h>

// 3 functions
// gmttrans_f

/************************************************************************************
 * This C function store the re-ordered input 2D grid (as an array) into a
 * pre-allocated array for GMT API GMT_GRID.
 *
 * int/float/double *p    ----  Original 2D grid. (1 by nx*ny)
 * int              nx    ----  x size.
 * int              ny    ----  y size.
 * int/float/double *pp   ----  GMT adapted 2D grid. (1 by [nx+pad[0]+pad[1]] * [ny+pad[2]+pad[3]])
 * int              *pad  ----  padding. Here I only figure out the longitude direction
 * 										 periodic BC. Will take incorrect grid as a coorect grid:
 *
 * 								if pad={1,2,3,4}:
 * 								    	W E S N
 * 								(usually just use pad={2,2,2,2})
 *
 * 								p(incorrect lon periodic value
 * 								  last column will be changed to the first column):
 *
 * 							t^		4 8 12 16 20 24
 * 							a|		3 7 11 15 19 23
 * 							L|		2 6 10 14 18 22
 * 									1 5 9  13 17 21
 *
 * 									-> Lon.
 *
 * 								pp:
 *
 * 								0 0 0 0	   12 11 10 9 	 0 0 0
 * 								0 0 0 0	   8  7  6  5 	 0 0 0
 *                              0 0 0 0                  0 0 0
 * 								0 0 0 0	   4  3  2  1 	 0 0 0
 * 								0 0 0 0	   20 19 18 17	 0 0 0
 * 								0 0 0 0	   16 15 14 13	 0 0 0	  n^
 * 								0 0 0 0	   12 11 10 9 	 0 0 0	  o|
 * 								0 0 0 0	   8  7  6  5 	 0 0 0    L|
 * 								0 0 0 0	   4  3  2  1 	 0 0 0
 *                              0 0 0 0                  0 0 0
 * 								0 0 0 0	   20 19 18 17	 0 0 0
 *
 * 										 Lat.
 * 										 <--
 *
 *
 * 						            -------------
 *
 *
 * 								p (correct lon periodic value):
 *
 * 							t^		4 8 12 16 20 4
 * 							a|		3 7 11 15 19 3
 * 							L|		2 6 10 14 18 2
 * 									1 5 9  13 17 1
 *
 * 									-> Lon.
 *
 * 								pp:
 *
 * 								0 0 0 0	   12 11 10 9 	 0 0 0
 * 								0 0 0 0	   8  7  6  5 	 0 0 0
 *                              0 0 0 0                  0 0 0
 * 								0 0 0 0	   4  3  2  1 	 0 0 0
 * 								0 0 0 0	   20 19 18 17	 0 0 0
 * 								0 0 0 0	   16 15 14 13	 0 0 0	  n^
 * 								0 0 0 0	   12 11 10 9 	 0 0 0	  o|
 * 								0 0 0 0	   8  7  6  5 	 0 0 0    L|
 * 								0 0 0 0	   4  3  2  1 	 0 0 0
 *                              0 0 0 0                  0 0 0
 * 								0 0 0 0	   20 19 18 17	 0 0 0
 *
 * 										 Lat.
 * 										 <--
 *
 *
 * Shule Yu
 * Jan 22 2016
 *
 * Note: North / South side will use symmetry BC.
 *
 * Key words: redirection.
************************************************************************************/

void gmttrans_f(float *p, int nx, int ny, float *pp, int *pad){

	int   Cnt,Cnt2,Begin1,Begin2;
	float *aux=(float *)malloc(nx*ny*sizeof(float));

	for (Cnt=0;Cnt<4;Cnt++){
		if (pad[Cnt]<0){
			pad[Cnt]=0;
		}
	}

	// Gmt transfigure.
	for (Cnt=0;Cnt<nx*ny;Cnt++){
		pp[Cnt]=p[Cnt];
	}

	for (Cnt=0;Cnt<nx;Cnt++){
		reverse_array_f(pp+Cnt*ny,ny);
	}

	redirect_f(pp,nx,ny,aux);

	// Padding.
	for (Cnt=0;Cnt<(nx+pad[0]+pad[1])*(ny+pad[2]+pad[3]);Cnt++){
		pp[Cnt]=0;
	}


	for (Cnt=pad[3];Cnt<ny+pad[3];++Cnt){

		Begin1=Cnt*(nx+pad[0]+pad[1])+pad[0];
		Begin2=(Cnt-pad[3])*nx;



		for (Cnt2=0;Cnt2<nx-1;++Cnt2){
			pp[Begin1+Cnt2]=aux[Begin2+Cnt2];
		}
		pp[Begin1+nx-1]=aux[Begin2];
		aux[Begin2+nx-1]=aux[Begin2];

		for (Cnt2=0;Cnt2<pad[0];++Cnt2){
			pp[Begin1-pad[0]+Cnt2]=aux[Begin2+nx-1-(pad[0]-Cnt2)%(nx-1)];
		}
		for (Cnt2=0;Cnt2<pad[1];++Cnt2){
			pp[Begin1+nx+Cnt2]=aux[Begin2+1+Cnt2%(nx-1)];
		}
	}


	for (Cnt=0;Cnt<pad[3];++Cnt){
		Begin1=Cnt*(nx+pad[0]+pad[1]);
		Begin2=(2*pad[3]-Cnt)*(nx+pad[0]+pad[1]);
		for (Cnt2=0;Cnt2<nx+pad[0]+pad[1];++Cnt2){
			pp[Begin1+Cnt2]=pp[Begin2+Cnt2];
		}
	}

	for (Cnt=0;Cnt<pad[2];++Cnt){
		Begin1=(ny+pad[3]+Cnt)*(nx+pad[0]+pad[1]);
		Begin2=(ny+pad[3]-Cnt-2)*(nx+pad[0]+pad[1]);
		for (Cnt2=0;Cnt2<nx+pad[0]+pad[1];++Cnt2){
			pp[Begin1+Cnt2]=pp[Begin2+Cnt2];
		}
	}

	free(aux);
	return;
}
