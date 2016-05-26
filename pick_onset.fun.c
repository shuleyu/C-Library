#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<ASU_tools.h>

/***********************************************************
 * This C function find the onset of some trace, located
 * within some certain window and return the position of the
 * onset. If Onset exceed the window, return -1.
 *
 * double *p       ----  Input array.
 * int    npts     ----  Array length.
 * double delta    ----  Sampling rate.
 * int    W1       ----  Window position / left. 
 * int    Wlength  ----  Window length.
 *
 *
 * Shule Yu
 * Oct 13 2014
***********************************************************/

int pick_onset(double *p, int npts, double delta, int W1, int Wlength){

    double Noise1=-180.0;
    double Noise2=-5.0;
    double Criteria=0.1;

    double *tmpdata,AMP,Nlevel;
    int    C,N1,N2,count;

    // define noise window.
    N1=W1+ceil(Noise1/delta);
    N2=W1+ceil(Noise2/delta);

    // make derivative; absolute it.
    tmpdata=(double *)malloc((npts-1)*sizeof(double));

    for (count=0;count<npts-1;count++){
        tmpdata[count]=fabs(p[count+1]-p[count]);
    }

    // normalized it within given window.
    AMP=amplituded(tmpdata+W1,Wlength);
    for (count=0;count<npts-1;count++){
        tmpdata[count]/=AMP;
    }

    // find noise level; Define Criteria.
    Nlevel=0;
    for (count=N1;count<N2;count++){
        if (Nlevel<tmpdata[count]){
            Nlevel=tmpdata[count];
        }
    }

    if (Nlevel>Criteria){
        Criteria=Nlevel;
    }

    // find start point to begin downhill search.
    for (C=N2;C<npts-1;C++){
        if (tmpdata[C]>Criteria){
            break;
        }
    }

    // begin downhill search.
    for (count=C;count>N2;count--){
        if (tmpdata[count]<Nlevel){
            break;
        }
    }

    free(tmpdata);

    // return onset.
    if (count<W1 || count>W1+Wlength ){
        return -1;
    }
    else{
        return count;
    }
}
