// Done.

#include<math.h>
#include<ASU_tools.h>

/***********************************************************
 * This C function returns a triangle signal.
 * The signal is centered at its peak, amplitude is 1.
 *
 * double *p     ----  output signal, pre-mallocated space. (1*npts)
 * int    npts   ----  signal length.
 * double frac   ----  fraction of the non-zero part:
 *
 *	e.g:
 *                      * 
 *                     * *
 *                    *   *
 *                   *     *
 *        00000000000       00000000000
 *
 *		  frac = 7/NPTS = 7/29 = 0.33333
 * 
 *
 * Shule Yu
 * Dec 29 2016
 *
 * Key words: triangle function.
***********************************************************/

void trifun(double *p,int npts,double frac){

	if (frac<0) frac=0; // gives an impulse.

	int i,L=npts*frac;
	double INC=-2.0/(L+1);
    p[npts/2]=1;

    for (i=npts/2+1;i<npts;i++){
        p[i]=p[i-1]+INC;
		if (p[i]<0) p[i]=0;
        p[npts/2-(i-npts/2)]=p[i];
    }
	p[0]=p[1]+INC;
	if (p[0]<0) p[0]=0;

	return;
}
