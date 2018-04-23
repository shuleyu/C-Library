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


    int    count,count2,count3,*shift=NULL,*choose;
    double *weight=NULL;

    choose=(int *)malloc(nptsx*BootNum*sizeof(int));

    // Create random number.
    random_int(0,nptsx-1,choose,nptsx*BootNum);


    // Stack and get weighted mean for each resamples.
    for (count=0;count<BootNum;count++){

        for (count2=0;count2<nptsy;count2++)
            Boot[count][count2]=0;

        double SumW=0;
        for (count2=0;count2<nptsx;count2++){
            int Choose=choose[count*nptsx+count2];
            double Weight=(flag_weight==1?w[Choose]:1);
            SumW+=fabs(Weight);
            for (count3=0;count3<nptsy;count3++){
                Boot[count][count3]+=Weight*p[Choose][count3];
            }
        }

        for (count2=0;count2<nptsy;count2++){
            Boot[count][count2]/=SumW;
        }
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

    free(tmparray);
    free(choose);

    return ;
}
