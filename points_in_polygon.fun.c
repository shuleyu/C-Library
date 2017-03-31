#include<stdio.h>
#include<math.h>
#include<ASU_tools.h>

/**************************************************************
 * This C function decide weather given points on 2D plane
 * located inside one give 2D polygon using Winding Number
 * method described in the reference link.
 *
 * double *x      ----  x coordinates of given ponits. (1*npts_P)
 * double *y      ----  y coordinates of given points. (1*npts_P)
 * int    npts_P  ----  Number of given points.
 * double *xx     ----  x coordinates of the polygon. (1*npts_L)
 * double *yy     ----  y coordinates of the polygon. (1*npts_L)
 * int    npts_L  ----  Number of polygon vertices.
 *
 * 						Let there be an edge between (xx[C],yy[C])
 * 						and (xx[C+1],yy[C+1]). Also (xx[0],yy[0])
 * 						is adjacent to (xx[npts_L-1],yy[npts_L-1]).
 *
 * int    *WN     ----  Outputs. (1*npts_P)
 * 						gives the Winding Number (WN) of each point.
 *
 * 						If WN[Cnt]==0, point Cnt is outside.
 * 						If WN[Cnt]!=0, point Cnt is inside.
 *
 * 						Notice: We define the inside of the polygon
 * 						        as the left hand side area as one
 * 						        walks on its edge in the given array.
 *
 * 						        Points located on the left and bottom 
 * 						        edges are decided to be inside.
 *
 *
 * Shule Yu
 * Dec 09 2015
 *
 * Key words: points inside polygon, winding number.
 * Reference: http://geomalgorithms.com/a03-_inclusion.html
****************************************************************/

void points_in_polygon(double *x,double *y,int npts_P,double *xx,double *yy,int npts_L,int *WN){

	int Cnt,Cnt2;

	for (Cnt=0;Cnt<npts_P;Cnt++){

		WN[Cnt]=0;

		for (Cnt2=0;Cnt2<npts_L;Cnt2++){

			double ex1,ey1,ex2,ey2;

			ex1=xx[Cnt2];
			ey1=yy[Cnt2];
			ex2=xx[(Cnt2+1)%npts_L];
			ey2=yy[(Cnt2+1)%npts_L];

			if (ey1<=y[Cnt]){
				if (y[Cnt]<ey2 && crossproduct_2d(ex1-x[Cnt],ey1-y[Cnt],ex2-x[Cnt],ey2-y[Cnt])>0){
					WN[Cnt]++;
				}
			}
			else{
				if (ey2<=y[Cnt] && crossproduct_2d(ex1-x[Cnt],ey1-y[Cnt],ex2-x[Cnt],ey2-y[Cnt])<0){
					WN[Cnt]--;
				}
			}
		}
	}

	return;
}
