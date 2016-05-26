#include<stdio.h>
#include<ASU_tools.h>

// 3 functions
// normalize
// normalized
// normalize_window

/***********************************************************
 * This C function returns the amplitude of an array.
 * Simutaneously, normalize the input array using the
 * amplitude.
 *
 * (for normalize_window:)
 * Normalize the input double array within a certain window.
 * Return amplitude within the window.
 *
 * flost/double *p   ---- Array pointer.
 * int          npts ---- Array npts.
 *
 * (for normalize_window:)
 * int    W1        ---- Window begin position.  ( in npts )
 * int    Wlength   ---- Window length. ( in npts )
 *
 *
 * Shule Yu
 * Feb 13 2014
 *
 * Note: original data destroyed.
 * Key words: normalize.
***********************************************************/

double normalize(float *p, int npts){

    int    count;
    double AMP;

    // Find AMP.
    AMP=amplitude(p,npts);
    if (AMP==0.0){
        printf("In %s: Array is zeros ...\n",__func__);
        return 1;
    }

    // Normalize array.
    for (count=0;count<npts;count++){
        p[count]/=AMP;
    }

    return AMP;
}

double normalized(double *p, int npts){

    int    count;
    double AMP;

    // Find AMP.
    AMP=amplituded(p,npts);
    if (AMP==0.0){
        printf("In %s: Array is zeros ...\n",__func__);
        return 1;
    }

    // Normalize array.
    for (count=0;count<npts;count++){
        p[count]/=AMP;
    }

    return AMP;
}

double normalize_window(double *p, int npts,int W1,int Wlength){

    if (W1+Wlength>npts){
        Wlength=npts-W1;
    }

    int    count;
    double AMP;

    // Find AMP.
    AMP=amplituded(p+W1,Wlength);
    if (AMP==0.0){
        printf("In %s: Array is zeros ...\n",__func__);
        return 1;
    }

    // Normalize array.
    for (count=0;count<npts;count++){
        p[count]/=AMP;
    }

    return AMP;
}
