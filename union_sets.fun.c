#include<ASU_tools.h>

/***********************************************************
 * This C function returns the union result of input close
 * sets.
 *
 * double *x         ----  Lower limits array, length is npts.
 * double *y         ----  Upper limits array, length is npts.
 * double *xx        ----  New Lower limits array.
 * double *yy        ----  New Upper limits array.
 *                         These four arrays should all have
 *                         "npts" spaces.
 * int    npts       ----  Number of sets.
 * int    *new_npts  ----  Number of sets after the union.
 *
 * Shule Yu
 * Aug 12 2014
 *
 * Key words: union, set
***********************************************************/

void union_sets(double *x, double *y, double *xx, double *yy, int npts, int *new_npts){

    if (npts==0){
        (*new_npts)=0;
        return ;
    }

    int    count,remove;
    double lowermost,uppermost,tmp;

    (*new_npts)=0;
    while (npts>0){
        lowermost=x[0];
        uppermost=y[0];
        for (count=0;count<npts;count++){
            if (x[count]>y[count]){
                tmp=y[count];
                y[count]=x[count];
                x[count]=tmp;
            }
            if (lowermost>x[count]){
                lowermost=x[count];
                uppermost=y[count];
            }
        }
        remove=0;
        for (count=0;count<npts;count++){
            if (x[count]<=uppermost && x[count]>=lowermost){
                if (uppermost<y[count]){
                    uppermost=y[count];
                }
                remove++;
            }
            else{
                x[count-remove]=x[count];
                y[count-remove]=y[count];
            }

        }
        xx[(*new_npts)]=lowermost;
        yy[(*new_npts)]=uppermost;

        (*new_npts)++;
        npts-=remove;
    }

    return;
}
