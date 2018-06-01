#include<stdlib.h>
#include<math.h>
#include<ASU_tools.h>

/***********************************************************
 * This C function compute a circle geographyic binning
 * results. Update the bin center to the average position.
 *
 * double *plon        ----  Sampling longitudes.
 * double *plat        ----  Sampling latitudes.
 * int    N            ----  Sampling #.
 * double *blon        ----  Bin longitudes.
 * double *blat        ----  Bin latitudes.
 * double *radius      ----  Bin circle radius.
 * int    M            ----  Bin #.
 * int    **index      ----  Output index matrix. ( N * M )
 *
 * Shule Yu
 * Jun 23 2015
 *
 * Note: original bin information destroyed.
 * Key words: geographic bin, circle, update.
***********************************************************/

void cbin_update(double *plon, double *plat, int N, double *blon, double *blat, double *radius, int M, int **index){

    int count,count2,count3;

    // Judge each trace.
    for (count=0;count<N;count++){
        for (count2=0;count2<M;count2++){
            if (gcpdistance(plon[count],plat[count],blon[count2],blat[count2])<=radius[count2]){
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

    return;
}
