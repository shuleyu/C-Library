#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<ASU_tools.h>

// 2 functions:
// meshsize
// meshthem

/***********************************************************
 * This C function returns the meshing size:
 *
 * double lowerbound   ----  Grid lower bound.
 * double higherbound  ----  Grid higher bound.
 * double delta        ----  Grid interval.
 * int    flag         ----  mode.
 *                                =0: fix delta; last grid value
 *                                    is less equal to higherbound.
 *                                =1: decrease delta a little bit
 *                                    such that the last grid value
 *                                    equals to higherbound.
 *
 * Return value: The array size needed for the mesh.
 *
 * Shule Yu
 * Jan 07 2016
 *
 * Key words: meshing size.
***********************************************************/

int meshsize(double lowerbound, double higherbound, double delta, int flag){

    if (flag==0){
        return 1+(int)floor((higherbound-lowerbound)/delta);
    }
    else if (flag==1){
        return 1+(int)ceil((higherbound-lowerbound)/delta);
    }
    else{
        printf("In %s: Flag error ...\n",__func__);
        return -1;
    }
}

/************************************************************
 * This C function returns the meshing result.
 *
 * double *res         ----  grid result.
 * int    npts         ----  grid array size.
 * double lowerbound   ----  Grid lower bound.
 * double higherbound  ----  Grid higher bound.
 * double delta        ----  Grid interval.
 * int    flag         ----  mode.
 *                                =0: fix delta; last grid value
 *                                    is less equal to higherbound.
 *                                =1: decrease delta a little bit
 *                                    such that the last grid value
 *                                    equals to higherbound.
 *                                =2: ignore delta. Use lowerbound
 *                                       higherbound and npts to create
 *                                       the grid.
 *
 * Return value: actual interval.
 * 
 * Shule Yu
 * Jan 07 2016
 *
 * Key words: meshing result.
************************************************************/

double meshthem(double *res, int npts, double lowerbound, double higherbound, double delta, int flag){

    int NPTS,Cnt;

    if (flag==0 || flag==1){
        NPTS=meshsize(lowerbound,higherbound,delta,flag);
        if (NPTS>npts){
            printf("In %s: Array size not big enough ...\n",__func__);
            return -1.0;
        }
    }

    if (flag==0){
        for (Cnt=0;Cnt<NPTS;Cnt++){
            res[Cnt]=lowerbound+Cnt*delta;
        }
    }
    else if (flag==1){
        delta=(higherbound-lowerbound)/(NPTS-1);
        for (Cnt=0;Cnt<NPTS;Cnt++){
            res[Cnt]=lowerbound+Cnt*delta;
        }
    }
    else if (flag==2){
        delta=(higherbound-lowerbound)/(npts-1);
        for (Cnt=0;Cnt<npts;Cnt++){
            res[Cnt]=lowerbound+Cnt*delta;
        }
    }
    else{
        printf("In %s: Flag error ...\n",__func__);
        return -1;
    }

    return delta;
}
