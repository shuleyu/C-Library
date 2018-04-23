#include<stdio.h>
#include<stdlib.h>
#include<ASU_tools.h>

// 3 functions
// min_vald
// max_vald
// max_val_i
// minval_f
// maxval_f

/**************************************************************
 * This C function returns the minimum/maximum valule of input
 * array. Also calculate its position.
 *
 * double *p   ---- Array pointer.
 * int    npts ---- Array npts.
 * int    *pp  ---- Position. so that min/max=p[pp].
 *
 * Shule Yu
 * May 23 2014
 *
 * Key words: minimum, maximum
**************************************************************/

double min_vald(double *p, int npts, int *pp){

    if (npts<=0){
        printf("In %s: Npts error !\n",__func__);
        exit(1);
    }

    int    count;
    double val=1/0.0;

    for (count=0;count<npts;count++){
        if (val>p[count]){
            val=p[count];
            (*pp)=count;
        }
    }

    return val;
}

double max_vald(double *p, int npts, int *pp){

    if (npts<=0){
        printf("In %s: Npts error !\n",__func__);
        exit(1);
    }

    int    count;
    double val=-1/0.0;

    for (count=0;count<npts;count++){
        if (val<p[count]){
            val=p[count];
            (*pp)=count;
        }
    }

    return val;
}

int max_val_i(int *p, int npts, int *pp){

    if (npts<=0){
        printf("In %s: Npts error !\n",__func__);
        exit(1);
    }

    int count;
    int val=p[0];

    for (count=1;count<npts;count++){
        if (val<p[count]){
            val=p[count];
            (*pp)=count;
        }
    }

    return val;
}

float maxval_f(float *p, int npts, int *pp){

    if (npts<=0){
        printf("In %s: Npts error !\n",__func__);
        exit(1);
    }

    int count;
    float val=p[0];

    for (count=1;count<npts;count++){
        if (val<p[count]){
            val=p[count];
            (*pp)=count;
        }
    }

    return val;
}

float minval_f(float *p, int npts, int *pp){

    if (npts<=0){
        printf("In %s: Npts error !\n",__func__);
        exit(1);
    }

    int    count;
    float  val=p[0];

    for (count=0;count<npts;count++){
        if (val>p[count]){
            val=p[count];
            (*pp)=count;
        }
    }

    return val;
}
