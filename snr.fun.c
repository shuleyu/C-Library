#include<stdio.h>
#include<stdlib.h>
#include<ASU_tools.h>

// 2 functions
// snr_envelope
// snr_peak

/***********************************************************
 * This C function evaluate the signal to noise ratio of
 * input signal (S).
 *
 * (for snr_envelope:)
 * Step1. Calculate S^2+H^2. H is the Hilbert transform of S.
 * Step2. Integrate between singal window and noise window.
 * Step3. Return the ratio, normalized by window lengths.
 *
 * (for snr_peak:)
 * Take the ratio of amplitude within signal window and 
 * the amplitude within the noise window as SNR.
 *
 * double *p    ----  Input array pointer.
 * int    npts  ----  Array npts.
 * int    nloc  ----  Noise start position.
 * int    nlen  ----  Noise length.
 * int    sloc  ----  Signal start position.
 * int    slen  ----  Signal length.
 *
 * Shule Yu
 * Oct 12 2014
 *
 * Key words: signal to noise ratio, SNR
***********************************************************/

double snr_envelope(double *p, int npts,int nloc,int nlen,int sloc,int slen){

    int    count;
    double Slevel,Nlevel,*enveloped_p;

	if (nloc<0 || nloc>npts || nlen<0 || nloc+nlen>npts){
		printf("In %s: Noise window error ...\n",__func__);
		return 0.0;
	}
	if (sloc<0 || sloc>npts || slen<0 || sloc+slen>npts){
		printf("In %s: Signal window error ...\n",__func__);
		return 0.0;
	}

    enveloped_p=(double *)malloc(npts*sizeof(double));
    envelope_hilbert(p,npts,enveloped_p);

    // integrate envelope using Simpson's rule. (omit multiply by h/3).
    Slevel=0;
    Slevel+=enveloped_p[sloc];
    for (count=1;count<slen-1;count++){
        Slevel+=(count%2+1)*2*enveloped_p[sloc+count];
    }
    Slevel+=enveloped_p[sloc+slen-1];

    Nlevel=0;
    Nlevel+=enveloped_p[nloc];
    for (count=1;count<nlen-1;count++){
        Nlevel+=(count%2+1)*2*enveloped_p[nloc+count];
    }
    Nlevel+=enveloped_p[nloc+nlen-1];

    free(enveloped_p);

    // average with respect to their length.
    return Slevel/Nlevel*(1.0*nlen/slen);
}

double snr_peak(double *p,int npts,int nloc,int nlen,int sloc,int slen){

	if (nloc<0 || nloc>npts || nlen<0 || nloc+nlen>npts){
		printf("In %s: Noise window error ...\n",__func__);
		return 0.0;
	}
	if (sloc<0 || sloc>npts || slen<0 || sloc+slen>npts){
		printf("In %s: Signal window error ...\n",__func__);
		return 0.0;
	}

    return amplituded(p+sloc,slen)/amplituded(p+nloc,nlen);
}
