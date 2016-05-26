#include<math.h>
#include<ASU_tools.h>

// 2 functions
// taper
// taperd

/***********************************************************
 * This C function taper input signal, using Hanning Window.
 *
 * float/double *p     ----  Array ponter.
 * int          npts   ----  Data length.
 * double       width  ----  Taper window half-length.
 *                           ( proportional to npts )
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
