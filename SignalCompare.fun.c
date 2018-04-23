#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<ASU_tools.h>

/***********************************************************
 * This C function compares two input signal.
 *
 * double *s1        ----  Signal 1.
 * int     n1        ----  Signal 1 length.
 * int     p1        ----  Signal 1 peak.
 * double *s2        ----  Signal 2.
 * int     n2        ----  Signal 2 length.
 * int     p2        ----  Signal 2 peak.
 * double  delta     ----  Sampling rate.
 * double  t1        ----  Diff compare begin window (relative to peak, in sec.).
 * double  t2        ----  Diff compare end window (relative to peak, in sec.).
 * double  AMPlevel  ----  CC compare part. (compare the part above this amplitude value)
 * int     *Shift    ----  CC result (npts of Shift; original position: peaks are overlaped)
 * double  *CCC      ----  CC result, cross-correlation coefficient.
 * double  *CCDiff   ----  At the best fit Shift, mean|s1-s2| of overlaped portion of above AMPlevel.
 * double  *CCLDiff  ----  At the best fit Shift, mean|s1-s2| of t1 ~ t2.
 * double  *Diff     ----  CC across window t1~t2, at the best shift, mean|s1-s2| of t1 ~ t2.
 *
 * Shule Yu
 * Dec 03 2016
 *
 * Note: The two signals should be the same sampling rate delta.
 *       The two signals peak s1[p1] and s2[p2] should = 1. (namely they are pre-normalized).
 *
 * Key words: compare
***********************************************************/


int SignalCompare(double *s1, int n1, int p1, double *s2, int n2, int p2,
                   double delta, double t1, double t2, double AMPlevel,
                   int *Shift, double *CCC, double *CCDiff, double *CCLDiff,double *Diff){

    // Check input.
    int W1=(int)ceil(t1/delta),W2=(int)ceil(t2/delta);
    if (p1<=0 || p1>=n1-1 || p2<=0 || p2>=n2-1){
        printf("In %s: peak position / signal length error ! \n",__func__);
        printf("p1: %d, n1: %d.\np2: %d, n2: %d.",p1,n1,p2,n2);
        return 1;
    }
    if(p1+W1<0 || p1+W2>=n1){
        printf("In %s: s1 window error ! \n",__func__);
        return 2;
    }
    if(p2+W1<0 || p2+W2>=n2){
        printf("In %s: s2 window error ! \n",__func__);
        return 3;
    }
    if (s1[p1]<0 || s2[p2]<0){
        printf("In %s: s1/s2 polarity error ! \n",__func__);
        printf("p1: %.2lf.\np2: %.2lf.\n",s1[p1],s2[p2]);
        return 4;
    }
    if (s1[p1]<0.9 || s2[p2]<0.9){
        printf("In %s: s1/s2 not pre-normalized ? \n",__func__);
        printf("p1: %.2lf.\np2: %.2lf.\n",s1[p1],s2[p2]);
        return 5;
    }


    // Find the part above AMPlevel on s1.
    int X_B,X_E,s1Len;

    for (X_B=p1;X_B>=0;X_B--){
        if (s1[X_B]<AMPlevel){
            X_B++;
            break;
        }
    }
    for (X_E=p1;X_E<n1;X_E++){
        if (s1[X_E]<AMPlevel){
            break;
        }
    }
    s1Len=X_E-X_B;


    // Find the part above AMPlevel on s2.
    int Y_B,Y_E,s2Len;

    for (Y_B=p2;Y_B>=0;Y_B--){
        if (s2[Y_B]<AMPlevel){
            Y_B++;
            break;
        }
    }
    for (Y_E=p2;Y_E<n2;Y_E++){
        if (s2[Y_E]<AMPlevel){
            break;
        }
    }
    s2Len=Y_E-Y_B;


    // Get rid of the square below AMPlevel, then normalize peak to 1.

    double *s1_CC;
    s1_CC=(double *)malloc(s1Len*sizeof(double));
    for (int index=0;index<s1Len;index++){
        s1_CC[index]=s1[X_B+index]-AMPlevel;
    }
    normalized(s1_CC,s1Len);


    double *s2_CC;
    s2_CC=(double *)malloc(s2Len*sizeof(double));

    for (int index=0;index<s2Len;index++){
        s2_CC[index]=s2[Y_B+index]-AMPlevel;
    }
    normalized(s2_CC,s2Len);


    // Do cross-correlation.
    CC(s1_CC,s1Len,s2_CC,s2Len,Shift,CCC);


    // Calculate mean|s1-s2| within the CC overlaping window.
    int X1,Y1,Len;
    if((*Shift)<0){
        X1=0;
        Y1=-(*Shift);
        Len=(s1Len<s2Len-Y1)?s1Len:(s2Len-Y1);
    }
    else{
        X1=(*Shift);
        Y1=0;
        Len=(s2Len<s1Len-X1)?s2Len:(s1Len-X1);
    }

    (*CCDiff)=0;
    for (int index=0;index<Len;index++){
        (*CCDiff)+=fabs(s1_CC[X1+index]-s2_CC[Y1+index]);
    }
    (*CCDiff)/=Len;


    // Correct Shift to originally align with peaks.
    (*Shift)-=((p1-X_B)-(p2-Y_B));


    // Using the CC shift, calculate mean|s1-s2| between t1 ~ t2.
    (*CCLDiff)=0;
    for (int index=W1;index<W2;index++){
        (*CCLDiff)+=fabs(s1[p1+index]-s2[p2+index-(*Shift)]);
    }
    (*CCLDiff)/=(W2-W1);


    // Calculate shift (over larger window), then calculate
    // mean|s1-s2| between t1~t2.
    int shift;
    double ccc;
    CC(s1+p1+W1,W2-W1,s2+p2+W1,W2-W1,&shift,&ccc);

    if(shift<0){
        X1=p1+W1;
        Y1=p2+W1-shift;
        Len=(W2-W1)+shift;
    }
    else{
        X1=p1+W1+shift;
        Y1=p2+W1;
        Len=(W2-W1)-shift;
    }

    (*Diff)=0;
    for (int index=0;index<Len;index++){
        (*Diff)+=fabs(s1[X1+index]-s2[Y1+index]);
    }
    (*Diff)/=Len;


    // Free space.
    free(s1_CC),free(s2_CC);

    return 0;
}
