#include<stdio.h>
#include<math.h>
#include<ASU_tools.h>

// 3 functions:
// amplitude
// amplituded
// max_ampd

/***********************************************************
 * This C function returns the amplitude of an array.
 *
 * (for max_ampd:)
 * finds the position the first amplitdue, return its
 * polarity.
 *
 * float/double *p    ----  Array pointer.
 * int          npts  ----  Array npts.
 *
 * (for max_ampd:)
 * int    *pp  ---- Position. so that amp=|p[pp]|.
 *
 * Shule Yu
 * Feb 21 2014
 *
 * Key words: amplitude
***********************************************************/

double amplitude(float *p, int npts){

    if (npts<=0){
        printf("In %s: NPTS too small ...\n",__func__);
        return 0;
    }

    int    count;
    double AMP=-1/0.0;

    for (count=0;count<npts;count++){
        if (AMP<fabs(p[count])){
            AMP=fabs(p[count]);
        }
    }

    return AMP;
}

double amplituded(double *p, int npts){

    if (npts<=0){
        printf("In %s: NPTS too small ...\n",__func__);
        return 0;
    }

    int    count;
    double AMP=-1/0.0;

    for (count=0;count<npts;count++){
        if (AMP<fabs(p[count])){
            AMP=fabs(p[count]);
        }
    }

    return AMP;
}

int max_ampd(double *p, int npts, int *pp){

    if (npts<=0){
        printf("In %s: NPTS too small ...\n",__func__);
        return 0;
    }

    int    count;
    double AMP=-1/0.0;

    for (count=0;count<npts;count++){
        if (AMP<fabs(p[count])){
            AMP=fabs(p[count]);
            (*pp)=count;
        }
    }

    if (p[(*pp)]>0){
        return 1;
    }
    else {
        return -1;
    }
}
