#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<fftw3.h>
#include<ASU_tools.h>

/***********************************************************
 * This C function returns a signal represent a futterman
 * T-Star operation.
 *
 * double delta  ----  Sampling rate.
 * int    npts   ----  Number of points. (ensure delta * npts > 10 sec.)
 * double ts     ----  tstar operator (in sec.)
 * double *ans   ----  output Array pointer (1*npts).
 *
 * Shule Yu
 * Mar 08 2016
 *
 * Key words: Tstar, futterman.
 * Note: Modified from Grand's code, get the code from ed. 
 *       The code is modified such that ts<=0 gives a
 *       delta function peaking at t=1 sec.
***********************************************************/

void tstar(double delta, int npts, double ts, double *ans){

    if (npts<=1){
        printf("In %s: NPTS too small ...\n",__func__);
        return;
    }

	int Cnt;
	if (ts<=0){
		for (Cnt=0;Cnt<npts;++Cnt){
			ans[Cnt]=0;
		}
		ans[(int)(1/delta)]=1;
		return;
	}

	int flag;
	flag=0;
	if (npts%2==1){
		npts++;
		flag=1;
	}

	double c,f,df;
    fftw_complex *in;
    fftw_plan    p1;
	double *out;

	df=1.0/delta/npts;
    out=(double *)malloc(npts*sizeof(double));
    in=(fftw_complex *)fftw_malloc((npts/2+1)*sizeof(fftw_complex));


    // Define ifft transform plan.
    p1=fftw_plan_dft_c2r_1d(npts,in,out,FFTW_MEASURE);

	
	// Put attenuation scheme into the ifft plan.
	in[0][0]=1.0;
	in[0][1]=0.0;
	for (Cnt=1;Cnt<npts/2+1;++Cnt){
		f=df*Cnt;
		c=2*f*ts*(log(f)-M_PI*8/ts+M_PI*0.65);
		in[Cnt][0]=exp(-M_PI*f*ts)*cos(c);
		in[Cnt][1]=exp(-M_PI*f*ts)*sin(c);
	}

	// Run ifft.
	fftw_execute(p1);

	if (flag==1){
		npts--;
	}

	// Output.
	for (Cnt=0;Cnt<npts;++Cnt){
		ans[Cnt]=exp(M_PI*ts)*out[Cnt];
	}

	// Normalize 
    free(out);
    fftw_free(in);
    fftw_destroy_plan(p1);

    return;
}
