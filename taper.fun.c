#include<math.h>
#include<ASU_tools.h>

// 3 functions
// taper
// taperd
// taperd_section

/***********************************************************
 * This C function taper input signal, using Hanning Window.
 *
 * float/double *p     ----  Array ponter.
 * int          npts   ----  Data length.
 * double       width  ----  Taper window half-length.
 *                           ( proportional to npts:
 *                             if width=0.5, window cover
 *                             the whole signal)
 * e.g.
 *                         Signal:    ************************* (npts=25)
 *                        Tapered:    tttt*****************tttt (width=4/25)
 *
 *
 *
 * for taperd_section:
 * double       zerowidth  ----  Zero out the section in this window.
 *
 * e.g.
 *                         Signal:    ************************* (npts=25)
 *                  After ZeroOut:    0000*****************0000 (zerowidth=4/25)
 *                     Then Taper:    0000tttttt*****tttttt0000 (width=6/(25-8))
 *
 *
 * Shule Yu
 * Feb 14 2014
 *
 * Note: Original data destroyed.
 * Key words: Hanning taper.
 *
 * Reference:
 *     ~~~~~~~~~~ sac: help taper ~~~~~~~~~~~~
 *      for the edges (index within J, whose
 *      length is defined by N and width)
 *
 *      DATA(J)=DATA(J)*(F0-F1*COS(OMEGA*(J-1))
 *
 *       ======== ========= ===== ======
 *         TYPE     OMEGA     F0    F1
 *       ======== ========= ===== ======
 *        HANNING_  PI/N     0.50  0.50
 *       ======== ========= ===== ======
 *     ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
***********************************************************/

void taper(float *p, int npts, double width){

    int    N,count;
    double OMEGA,F0,F1,weight;

    N=ceil(npts*width);
    OMEGA=M_PI/N;
    F0=0.5;
    F1=0.5;
    for (count=0;count<N;count++){
        weight=F0-F1*cos(OMEGA*count);
        p[count]*=weight;
        p[npts-1-count]*=weight;
    }
    return;
}

void taperd(double *p, int npts, double width){

    int    N,count;
    double OMEGA,F0,F1,weight;

    N=ceil(npts*width);
    OMEGA=M_PI/N;
    F0=0.5;
    F1=0.5;
    for (count=0;count<N;count++){
        weight=F0-F1*cos(OMEGA*count);
        p[count]*=weight;
        p[npts-1-count]*=weight;
    }
    return;
}

void taperd_section(double *p, int npts, double zerowidth, double width){
	
	int count,N=(int)ceil(npts*zerowidth);
	
	for (count=0;count<N;count++){
		p[count]=0;
		p[npts-count-1]=0;
	}
	taperd(p+N,npts-2*N,width);

	return;
}
