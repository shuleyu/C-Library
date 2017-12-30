// Done. Use standard library function reverse():
// std::reverse(A.begin(),A.end());

#include<stdio.h>
#include<ASU_tools.h>

// 3 functions
// reverse_array
// reverse_array_f
// reverse_array_i

/***********************************************************
 * This C function reverse input double array.
 *
 * double/float/int *p    ----  Array pointer.
 * int              npts  ----  Array npts.
 *
 * Shule Yu
 * Aug 14 2014
 *
 * Key words: reverse, double.
 *
 * Note: original data destroied.
***********************************************************/

void reverse_array(double *p, int npts){

    int    count;
    double tmp_val;

    if (npts<1){
        printf("In %s: Array too short ...\n",__func__);
        return;
    }

    // Reverse array.
    for (count=0;count<npts/2;count++){
        tmp_val=p[count];
        p[count]=p[npts-1-count];
        p[npts-1-count]=tmp_val;
    }

    return;
}

void reverse_array_f(float *p, int npts){

    int   count;
    float tmp_val;

    if (npts<1){
        printf("In %s: Array too short ...\n",__func__);
        return;
    }

    // Reverse array.
    for (count=0;count<npts/2;count++){
        tmp_val=p[count];
        p[count]=p[npts-1-count];
        p[npts-1-count]=tmp_val;
    }

    return;
}
