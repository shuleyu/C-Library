#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<ASU_tools.h>

/****************************************************************************
 * This C function calculate the envelope of the input trace.
 * First make a Hilbert transform of input: y=Hilbert(x).
 * Then calculate the envelope as: z=sqrt(x^2+y^2).
 *
 * double *x    ----  1-D array pointer x (input signal, length is NPTS. )
 * int    NPTS  ----  NPTS.
 * double *ans  ----  Envelope signal ( output signal, length is NPTS. )
 *
 * Shule Yu
 * May 04 2015
 *
 * Dependence: fftw-3.
 *
 * Key words : fast fourier transform, envelope, hilbert.
****************************************************************************/

void envelope_hilbert(double *x,int NPTS,double *ans){

    int count;

    // Find Hilbert.
    phase_shift(x,NPTS,-90,ans);

    // Find Envelope.
    for (count=0;count<NPTS;count++){
        ans[count]=sqrt(pow(ans[count],2)+pow(x[count],2));
    }

    return;
}
