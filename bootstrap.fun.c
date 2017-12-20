// Marker.

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
 * double BootNum      ----  Number of iteration for bootstrapping.
 * double *avr         ----  Resample mean at each point. ( 1 * nptsy )
 * double *sigma       ----  Standard error at each point. ( 1 * nptsy )
 * double **Boot       ----  Resample result (weighted stacks). ( BootNum * nptsy )
 *
 * int    flag_weight  ----  Indicate if we have weight. (1 means yes we need)
 * double *w           ----  Weights for each row. (1 * nptsx)
 *                           Negative values means flip.
 *
 * Shule Yu
 * Dec 05 2014
 *
 * Key words: bootstrapping, statistics
 *
 * Reference:
 *     http://en.wikipedia.org/wiki/Bootstrapping_(statistics)#Approach
*********************************************************************************/

void bootstrap(double **p, int nptsx, int nptsy, int BootNum, double *avr, double *sigma, double **Boot, int flag_weight, double *w){

    int    count,count2,*shift=NULL,*choose;
    double **data,*weight;

    choose=(int *)malloc(nptsx*BootNum*sizeof(int));
    weight=(double *)malloc(nptsx*sizeof(double));
    data=(double **)malloc(nptsx*sizeof(double *));

    // Create random number.
    random_int(0,nptsx-1,choose,nptsx*BootNum);


    // Stack and get weighted mean for each resamples.
    for (count=0;count<BootNum;count++){
        for (count2=0;count2<nptsx;count2++){
            data[count2]=p[choose[count*nptsx+count2]];
            if (flag_weight==1){
                weight[count2]=w[choose[count*nptsx+count2]];
            }
			else{
				weight[count2]=1;
			}
        }
        shift_stack(data,nptsx,nptsy,0,shift,flag_weight,weight,Boot[count],sigma);
    }


	// Estimate the mean of resamples.
	shift_stack(Boot,BootNum,nptsy,0,shift,0,weight,avr,sigma);


    // Estimate the standard error of resamples.
	double *tmparray;
    tmparray=(double *)malloc(BootNum*sizeof(double));

    for (count=0;count<nptsy;count++){
        for (count2=0;count2<BootNum;count2++){
            tmparray[count2]=Boot[count2][count];
        }
        sigma[count]=std_d(tmparray,BootNum);
    }

    free(data);
    free(weight);
    free(tmparray);
    free(choose);

    return ;
}
