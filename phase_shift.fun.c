#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<fftw3.h>
#include<ASU_tools.h>

/*********************************************************************
 * This C function runs fft on input real signal, then shift each
 * frquency phase with a constant value. Output the ifft result.
 *
 * double *x      ----  1-D array pointer x (input signal).
 * int    NPTS    ----  NPTS.
 * double shift   ----  Constant phase shift value. ( in deg. )
 * double *y      ----  Phase shifted signal. ( length is NPTS. )
 *
 * Shule Yu
 * May 03 2015
 *
 * Dependence: fftw-3.
 *
 * Key words : fast fourier transform. phase shift.
*********************************************************************/

void phase_shift(double *x,int NPTS,double shift,double *y){

    int          count,NPTS2,flag;
    double       *in,a,b;
    fftw_complex *out;
    fftw_plan    p1,p2;

    flag=0;
    if ( NPTS%2==1 ){
        printf("In %s: NPTS is an odd number, pading it with zero ...\n",__func__);
        NPTS++;
        flag=1;
    }

    NPTS2=NPTS/2+1;
    in=(double *)malloc(NPTS*sizeof(double));
    out=(fftw_complex *)fftw_malloc(NPTS2*sizeof(fftw_complex));

    // Define fft transform plan.
    p1=fftw_plan_dft_r2c_1d(NPTS,in,out,FFTW_ESTIMATE);
    p2=fftw_plan_dft_c2r_1d(NPTS,out,in,FFTW_ESTIMATE);

    // Push data into the plan.
    for (count=0;count<NPTS-1;count++){
        in[count]=x[count];
    }
    if ( flag==1 ){
        in[NPTS-1]=0;
    }
    else{
        in[NPTS-1]=x[NPTS-1];
    }

    // Run fft.
    fftw_execute(p1);

    // Shift phase.
    for (count=0;count<NPTS2;count++){
        a=sqrt(pow(out[count][0],2)+pow(out[count][1],2));
        b=atan2(out[count][1],out[count][0]);
        out[count][0]=a*cos(b+shift*M_PI/180.0);
        out[count][1]=a*sin(b+shift*M_PI/180.0);
    }

    // Find modified signal.
    fftw_execute(p2);
    if ( flag==1 ){
        NPTS--;
    }
    for (count=0;count<NPTS;count++){
        y[count]=1.0*in[count]/NPTS;
    }

    fftw_destroy_plan(p1);
    fftw_destroy_plan(p2);
    fftw_free(out);
    free(in);

    return;
}
