// Done.
// Use C++ standard library "rotate".

#include<stdio.h>
#include<stdlib.h>
#include<ASU_tools.h>

// 2 functions:
// shift_array
// shift_array_f

/***********************************************************
 * This C function shift input double array, pad the spaces
 * periodically.
 *
 * shift > 0 : shift the array to +x direction ( towards right ).
 * shift < 0 : shift the array to -x direction ( towards left ).
 *
 * float/double *p     ----  Array pointer.
 * int          npts   ----  Array npts.
 * int          shift  ----  Shift npts.
 *
 * Shule Yu
 * Sept 21 2014
 *
 * Note: original data destroyed.
 *
 * Key words: shift.
***********************************************************/

void shift_array(double *p, int npts,int shift){

    if (npts<1){
        printf("In %s: Array too short ...\n",__func__);
        return;
    }

    if (shift==0 || npts < 2){
        return;
    }

    shift=shift%npts;

    if (shift>npts/2){
        shift-=npts;
    }
    if (shift<-npts/2){
        shift+=npts;
    }

    int    count;
    double *tmp;

    tmp=(double *)malloc(abs(shift)*sizeof(double));

    if ( shift<0 ){
        for (count=0;count<-shift;count++){
            tmp[count]=p[count];
        }
        for (count=0;count<npts+shift;count++){
            p[count]=p[count-shift];
        }
        for (count=npts+shift;count<npts;count++){
            p[count]=tmp[count-npts-shift];
        }
    }
    else {
        for (count=0;count<shift;count++){
            tmp[count]=p[npts-shift+count];
        }
        for (count=npts-1;count>shift-1;count--){
            p[count]=p[count-shift];
        }
        for (count=0;count<shift;count++){
            p[count]=tmp[count];
        }
    }

    free(tmp);
    return;
}

void shift_array_f(float *p, int npts,int shift){

    if (npts<1){
        printf("In %s: Array too short ...\n",__func__);
        return;
    }

    if (shift==0 || npts < 2){
        return;
    }

    shift=shift%npts;

    if (shift>npts/2){
        shift-=npts;
    }
    if (shift<-npts/2){
        shift+=npts;
    }

    int    count;
    double *tmp;

    tmp=(double *)malloc(abs(shift)*sizeof(double));

    if ( shift<0 ){
        for (count=0;count<-shift;count++){
            tmp[count]=p[count];
        }
        for (count=0;count<npts+shift;count++){
            p[count]=p[count-shift];
        }
        for (count=npts+shift;count<npts;count++){
            p[count]=tmp[count-npts-shift];
        }
    }
    else {
        for (count=0;count<shift;count++){
            tmp[count]=p[npts-shift+count];
        }
        for (count=npts-1;count>shift-1;count--){
            p[count]=p[count-shift];
        }
        for (count=0;count<shift;count++){
            p[count]=tmp[count];
        }
    }

    free(tmp);
    return;
}
