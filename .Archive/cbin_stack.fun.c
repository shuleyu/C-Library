#include<stdlib.h>
#include<math.h>
#include<ASU_tools.h>

// Two functions:
// cbin_stack
// cbin_stack_update

/***********************************************************
 * This C function compute a circle geographyic bin-stack
 * results.
 *
 * (for cbin_stack_update:)
 * Update the bin center to the average, also, apply an
 * Gaussian average using the distance to the updated center
 * as a parameter.
 *
 * double **data       ----  Input traces. (N * npts)
 * double *plon        ----  Trace longitudes.
 * double *plat        ----  Trace latitudes.
 * int    weight_flag  ----  =1 indicate use weight.
 *                           =0 indicate straigh stack.
 * double *weight      ----  Weight for each traces.
 * int    N            ----  Trace #.
 * int    npts         ----  Trace length.
 * double *blon        ----  Bin longitudes.
 * double *blat        ----  Bin latitudes.
 * double *radius      ----  Bin circle radius.
 * int    M            ----  Bin #.
 * int    **index      ----  Output index matrix. ( N * M )
 * double **stack      ----  Output stack. (M * npts)
 * double **std        ----  Output stack std. (M * npts)
 * 
 * (for cbin_stack_update:)
 * int    flag_smooth  ----  =1 indicate use gaussian smooth.
 *                           =0 indicate don't use smooth.
 * double       sigma  ----  sigma used for gaussian smooth.
 *
 * Shule Yu
 * Oct 26 2014
 *
 * Key words: geographic bin, circle, update, smooth
 *
 * (for cbin_stack_update:)
 * Note : original bin information destroyed.
***********************************************************/

void cbin_stack(double **data, double *plon, double *plat, int weight_flag, double *weight, int N, int npts, double *blon, double *blat, double *radius, int M, int **index, double **stack, double **std){

    int    count,count2,count3,*shift,N_tmp;
    double **p,*weight_tmp;

    weight_tmp=(double *)malloc(N*sizeof(double));
    p=(double **)malloc(N*sizeof(double *));
	shift=NULL;

    // Judge each trace.
    for (count=0;count<N;count++){
        for (count2=0;count2<M;count2++){
            if (gcpdistance(plon[count],plat[count],blon[count2],blat[count2])<radius[count2]){
                index[count][count2]=1;
            }
            else{
                index[count][count2]=0;
            }
        }
    }

    // Stack.
    for (count=0;count<M;count++){

        // Count how many traces.
        N_tmp=0;
        for (count2=0;count2<N;count2++){
            if (index[count2][count]==1){
                N_tmp++;
            }
        }

        count3=0;
        for (count2=0;count2<N;count2++){
            if (index[count2][count]==1){
                p[count3]=data[count2];
                weight_tmp[count3]=weight[count2];
                count3++;
            }
        }

        shift_stack(p,N_tmp,npts,0,shift,weight_flag,weight_tmp,stack[count],std[count]);
    }

    free(weight_tmp);
    free(p);
    return;
}

void cbin_stack_update(double **data, double *plon, double *plat, int weight_flag, double *weight, int N, int npts, double *blon, double *blat, double *radius, int M, int **index, double **stack, double **std, int flag_smooth, double sigma){

    int    count,count2,count3,*shift,N_tmp;
    double **p,*weight_tmp;

    weight_tmp=(double *)malloc(N*sizeof(double));
    p=(double **)malloc(N*sizeof(double *));
	shift=NULL;

    // Judge each trace.
    for (count=0;count<N;count++){
        for (count2=0;count2<M;count2++){
            if (gcpdistance(plon[count],plat[count],blon[count2],blat[count2])<radius[count2]){
                index[count][count2]=1;
            }
            else{
                index[count][count2]=0;
            }
        }
    }

    // Update bin center.

    for (count=0;count<M;count++){
        blat[count]=0;
        blon[count]=0;
        count3=0;
        for (count2=0;count2<N;count2++){
            if (index[count2][count]==1){
                blat[count]+=plat[count2];
                blon[count]+=plon[count2];
                count3++;
            }
        }

        if (count3!=0){
            blat[count]/=count3;
            blon[count]/=count3;
        }
    }

    // Stack.
    for (count=0;count<M;count++){

        // Count how many traces.
        N_tmp=0;
        for (count2=0;count2<N;count2++){
            if (index[count2][count]==1){
                N_tmp++;
            }
        }

        count3=0;
        for (count2=0;count2<N;count2++){
            if (index[count2][count]==1){
                p[count3]=data[count2];
                if (flag_smooth==1){
                    weight_tmp[count3]=weight[count2]*gaussian(gcpdistance(plon[count2],plat[count2],blon[count],blat[count])/radius[count],sigma,0);
                }
                else{
                    weight_tmp[count3]=weight[count2];
                }
                count3++;
            }
        }

        shift_stack(p,N_tmp,npts,0,shift,weight_flag,weight_tmp,stack[count],std[count]);
    }

    free(weight_tmp);
    free(p);
    return;
}
