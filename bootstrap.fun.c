#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<ASU_tools.h>

/*********************************************************************************
 * This C function apply bootstrapping test to input array.
 * Estimating the mean ( or weighted mean ) of each resample sets.
 * Considering weighting if weights are given.
 *
 * double **p          ----  Array pointer for 2D array input. (nptsx * nptsy)
 * int    nptsx        ----  Row number of p.
 * int    nptsy        ----  Column number of p. Each row is one signal.
 * int    flag_weight  ----  Indicate if we have weight. (1 means yes we need)
 * double *w           ----  Weights for each row. (1 * nptsx)
 *                           Negative values means flip row.
 * double BootNum      ----  Number of iteration for bootstrapping.
 * double **Boot       ----  BootStrap estimation of the mean, ( BootNum * nptsy )
 * double *sigma       ----  Estimate error of measurements from boostrap resamples. ( nptsy )
 *
 * Shule Yu
 * Dec 05 2014
 *
 * Key words: bootstrapping, statistics
 *
 * Reference:
 *     http://en.wikipedia.org/wiki/Bootstrapping_(statistics)#Approach
*********************************************************************************/

void bootstrap(double **p, int nptsx, int nptsy, int flag_weight, double *w, int BootNum, double **Boot, double *sigma){

    int    count,count2,*shift,*choose;
    double **data,*std,*weight,*tmparray;

    choose=(int *)malloc(nptsx*BootNum*sizeof(int));
    std=(double *)malloc(nptsy*sizeof(double));
    tmparray=(double *)malloc(BootNum*sizeof(double));
    weight=(double *)malloc(nptsx*sizeof(double));
    data=(double **)malloc(nptsx*sizeof(double *));
	shift=NULL;

    // Create random number.
    random_int(0,nptsx-1,choose,nptsx*BootNum);

    // Stack and get the estimate for means for each resamples.
    for (count=0;count<BootNum;count++){
        for (count2=0;count2<nptsx;count2++){
            data[count2]=p[choose[count*nptsx+count2]];
            if (flag_weight==1){
                weight[count2]=w[choose[count*nptsx+count2]];
            }
        }
        shift_stack(data,nptsx,nptsy,0,shift,flag_weight,weight,Boot[count],std);
    }

    // Estimate the standard error of measurements from bootstrap resamples.
    for (count=0;count<nptsy;count++){
        for (count2=0;count2<BootNum;count2++){
            tmparray[count2]=Boot[count2][count];
        }
        sigma[count]=std_d(tmparray,BootNum);
    }

    free(data);
    free(weight);
    free(std);
    free(tmparray);
    free(choose);

    return ;
}
