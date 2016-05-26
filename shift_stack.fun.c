#include<stdlib.h>
#include<math.h>
#include<ASU_tools.h>

/***********************************************************
 * This C function shift - stack input array, calculate standard
 * deviation, considering weighting if weights are given.
 *
 * Negative "shift" indicate this row should move foreward.
 * Positive "shift" indicate this row should move backward.
 *
 * double **p          ----  Array pointer for 2D array input.
 * int    nptsx        ----  Row number of p.
 * int    nptsy        ----  Column number of p.
 * int    flag_shift   ----  Indicate if we need shift. (1 means yes we need)
 * int    *shift       ----  Amount of shift for each row.
 * int    flag_weight  ----  Indicate if we need weight. (1 means yes we need)
 * double *w           ----  Weights for each row.
 *                           Negative value means flip.
 * double *stack       ----  Output value, stack.
 * double *std         ----  Output value, std.
 *
 * Shule Yu
 * Oct 01 2014
 *
 * Key words: shift stack, standard deviation.
***********************************************************/

void shift_stack(double **p, int nptsx, int nptsy, int flag_shift, int *shift, int flag_weight, double *w, double *stack, double *std){

    int    count,count2,P,*Shift;
    double *Weight,*tmparray,weight_sum;

    if (flag_shift==1){
        Shift=shift;
    }
    else{
        Shift=(int *)malloc(nptsx*sizeof(int));
        for (count=0;count<nptsx;count++){
            Shift[count]=0;
        }
    }

    if (flag_weight==1){
        Weight=w;
    }
    else{
        Weight=(double *)malloc(nptsx*sizeof(double));
        for (count=0;count<nptsx;count++){
            Weight[count]=1.0;
        }
    }

    // Calculate shift stack.
    for (count=0;count<nptsy;count++){
        stack[count]=0;
    }

    for (count=0;count<nptsx;count++){
        if (Weight[count]==0.0){
            continue;
        }
        P=(Shift[count]>0?Shift[count]:0);
        for (count2=P;count2<P+nptsy-abs(Shift[count]);count2++){
            stack[count2]+=(Weight[count]*p[count][count2-Shift[count]]);
        }
    }

    weight_sum=0;
    for (count=0;count<nptsx;count++){
        weight_sum+=fabs(Weight[count]);
    }

    if (weight_sum!=0){
        for (count=0;count<nptsy;count++){
            stack[count]/=weight_sum;
        }
    }

    // Calculate standard deviation.
    for (count=0;count<nptsy;count++){
        std[count]=0;
    }

    if (nptsx<2){
        if (flag_shift!=1){
            free(Shift);
        }
        if (flag_weight!=1){
            free(Weight);
        }
        return ;
    }

    tmparray=(double *)malloc(nptsx*sizeof(double));
    for (count=0;count<nptsy;count++){
        for (count2=0;count2<nptsx;count2++){
            if (count-Shift[count2]<0 || count-Shift[count2] > nptsy-1){
                tmparray[count2]=0;
            }
            else{
                tmparray[count2]=p[count2][count-Shift[count2]];
            }
        }
        std[count]=std_weight(tmparray,Weight,nptsx);
    }

    if (flag_shift!=1){
        free(Shift);
    }
    if (flag_weight!=1){
        free(Weight);
    }

    free(tmparray);

    return ;
}
