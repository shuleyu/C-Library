#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<fftw3.h>
#include<ASU_tools.h>

/*********************************************************************
 * This C function runs fft on input real signal and output the
 * amplitude and phase information.
 * Note: here we restrict NPTS to be an even number. Output spaces
 * are pre allocated.
 * Note: Didn't do the power normalization. (divide by NPTS)
 *
 * double **x      ----  2D array pointer x (input signal).
 * int    nptsx    ----  Number of traces.
 * int    NPTS     ----  NPTS.
 * double delta    ----  Sampling rate.
 * double *freq    ----  Frequency array. (output) length = NPTS/2+1
 * double **amp    ----  Amplitude array. (output) length = NPTS/2+1
 * double **phase  ----  Phase array.     (output) length = NPTS/2+1
 *
 * Shule Yu
 * Apr 28 2015
 *
 * Dependence: fftw-3.
 *
 * Key words : fast fourier transform.
***********************************************************/

void freq_amp_phase(double **x,int nptsx,int NPTS,double delta,double *freq,double **amp,double **phase){

    int          count,count2,NPTS2,flag;
    double       *in,df;
    fftw_complex *out;
    fftw_plan    p1;

    flag=0;
    if ( NPTS%2==1 ){
        NPTS++;
        flag=1;
    }

    NPTS2=NPTS/2+1;
    in=(double *)malloc(NPTS*sizeof(double));
    out=(fftw_complex *)fftw_malloc(NPTS2*sizeof(fftw_complex));
    df=1.0/delta/NPTS;

    // Define fft transform plan.
    p1=fftw_plan_dft_r2c_1d(NPTS,in,out,FFTW_MEASURE);

    // Find freq.
    for (count=0;count<NPTS2-1;count++){
        freq[count]=count*df;
    }
    if(flag==0){
        freq[NPTS2-1]=count*df;
    }

    for (count=0;count<nptsx;count++){

        // Push data into the fft plan.
        for (count2=0;count2<NPTS-1;count2++){
            in[count2]=x[count][count2];
        }
        if ( flag==1 ){
            in[NPTS-1]=0;
        }
        else{
            in[NPTS-1]=x[count][NPTS-1];
        }


        // Run fft.
        fftw_execute(p1);

        // Find amp.
        for (count2=0;count2<NPTS2-1;count2++){
            amp[count][count2]=sqrt(pow(out[count2][0],2)+pow(out[count2][1],2));
        }
        if(flag==0){
            amp[count][NPTS2-1]=sqrt(pow(out[NPTS2-1][0],2)+pow(out[NPTS2-1][1],2));
        }

        // Find phase.
        for (count2=0;count2<NPTS2-1;count2++){
            phase[count][count2]=atan2(out[count2][1],out[count2][0]);
        }
        if(flag==0){
            phase[count][NPTS2-1]=atan2(out[NPTS2-1][1],out[NPTS2-1][0]);
        }
    }

    fftw_destroy_plan(p1);
    fftw_free(out);
    free(in);

    return;
}
