// Done.

#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<sac.h>
#include<sacio.h>
#include<ASU_tools.h>

/*******************************************************************************************
 * This C function apply the butterworth filter on data. The filter is provided by SAC.
 *
 * double **p     ----  An 2D input array. ( nptsx * nptsy )
 * int    nptsx   ----  Number of traces.
 * int    nptsy   ----  Nubmer of data points for each traces.
 * double delta   ----  Data sampling rate.
 * int    order   ----  Filter order.
 * int    passes  ----  Pass.
 * double f       ----  Filter corner.  ( left corner for bandpass )
 * double **ans   ----  Output 2D array. ( nptsx * nptsy )
 *
 * (for butterworth_bp:)
 * double f2            ----  Filter right corner.
 *
 * Shule Yu
 * Nov 16 2015
 *
 * Key words: sac, filter, butterworth.
*******************************************************************************************/

void butterworth_lp(double **p, int nptsx, int nptsy, double delta, int order, int passes, double f, double **ans){

	int   Cnt,Cnt2;
	float *rawdata;
	rawdata=(float *)malloc(nptsy*sizeof(float));

	for (Cnt=0;Cnt<nptsx;Cnt++){
		for (Cnt2=0;Cnt2<nptsy;Cnt2++){
			rawdata[Cnt2]=p[Cnt][Cnt2];
		}

		xapiir(rawdata,nptsy,SAC_BUTTERWORTH,0.0,0.0,order,SAC_LOWPASS,0.0,f,delta,passes);

		for (Cnt2=0;Cnt2<nptsy;Cnt2++){
			ans[Cnt][Cnt2]=rawdata[Cnt2];
		}
	}

	free(rawdata);

	return ;
}

void butterworth_hp(double **p, int nptsx, int nptsy, double delta, int order, int passes, double f, double **ans){

	int   Cnt,Cnt2;
	float *rawdata;
	rawdata=(float *)malloc(nptsy*sizeof(float));

	for (Cnt=0;Cnt<nptsx;Cnt++){
		for (Cnt2=0;Cnt2<nptsy;Cnt2++){
			rawdata[Cnt2]=p[Cnt][Cnt2];
		}

		xapiir(rawdata,nptsy,SAC_BUTTERWORTH,0.0,0.0,order,SAC_HIGHPASS,f,0.0,delta,passes);

		for (Cnt2=0;Cnt2<nptsy;Cnt2++){
			ans[Cnt][Cnt2]=rawdata[Cnt2];
		}
	}

	free(rawdata);

	return ;
}

void butterworth_bp(double **p, int nptsx, int nptsy, double delta, int order, int passes, double f, double f2, double **ans){

	int   Cnt,Cnt2;
	float *rawdata;
	rawdata=(float *)malloc(nptsy*sizeof(float));

	for (Cnt=0;Cnt<nptsx;Cnt++){
		for (Cnt2=0;Cnt2<nptsy;Cnt2++){
			rawdata[Cnt2]=p[Cnt][Cnt2];
		}

		xapiir(rawdata,nptsy,SAC_BUTTERWORTH,0.0,0.0,order,SAC_BANDPASS,f,f2,delta,passes);

		for (Cnt2=0;Cnt2<nptsy;Cnt2++){
			ans[Cnt][Cnt2]=rawdata[Cnt2];
		}
	}

	free(rawdata);

	return ;
}
