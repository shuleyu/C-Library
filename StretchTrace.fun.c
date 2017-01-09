#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<ASU_tools.h>

/***********************************************************
 * This C function stretch input signal according given
 * parameters.
 *
 * double *p    ----  Array pointer.
 * int    npts  ----  Array npts.
 * int    Peak  ----  Stretch center position.
 * double Hor   ----  Horizontal stretch factor.
 *
 *                    Hor = 1 means the original trace.
 *                    Hor = 0.5 gives narrower trace, width
 *                              at certain amplitude becomes half.
 *                    Hor = 2 gives broader trace, width
 *                              at certain amplitude becomes doubled.
 *
 * double Ver   ----  Vertical stretch factor.
 *
 *                    Ver = 0 means the original trace.
 *                    Ver = 1 gives vertically shrinked trace, height (y-distance to peak)
 *                              at certain time becomes half.
 *                    Hor = -0.5 gives vertically expanded trace, height (y-distance to peak)
 *                              at certain amplitude becomes doubled.
 *
 * double delta ----  Sampling rate.
 * double *pp   ----  Output. Stretched traces. (1*npts, pre-allocated)
 *
 * Shule Yu
 * Nov 26 2016
 *
 * Key words: stretch
***********************************************************/

void StretchTrace(double *p, int npts, int Peak, double Hor, double Ver, double delta, double *pp){

    if (npts<=0){
        printf("In %s: NPTS too small ...\n",__func__);
        return;
    }

	int index,T1=0,T2=npts;

	double *time_old,*time_new,*amp_new;
	time_old=(double *)malloc(npts*sizeof(double));
	time_new=(double *)malloc(npts*sizeof(double));
	amp_new=(double *)malloc(npts*sizeof(double));
	for (index=0;index<npts;index++){
		time_old[index]=(index-Peak)*delta;
		time_new[index]=time_old[index]/Hor;
		if(time_new[index]<time_old[0]){
			T1=index+1;
		}
		if(T2==npts && time_new[index]>(npts-1-Peak)*delta){
			T2=index;
		}
	}

	if (Hor!=1){
		wiginterpd(time_old,p,npts,time_new+T1,amp_new+T1,T2-T1,0);
	}
	else{
		for (index=0;index<npts;index++) amp_new[index]=p[index];
	}

	double AMP=p[Peak];
	for (index=T1;index<T2;index++){
		pp[index]=amp_new[index]/AMP;
		pp[index]=(pp[index]+Ver)/(1+Ver);
		pp[index]=pp[index]*AMP;
	}

	for (index=0;index<T1;index++){
		pp[index]=pp[T1];
	}
	for (index=T2;index<npts;index++){
		pp[index]=pp[T2-1];
	}

	free(time_old);
	free(time_new);
	free(amp_new);

	return;
}
