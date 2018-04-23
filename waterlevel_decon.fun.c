#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<sac.h>
#include<fftw3.h>
#include<ASU_tools.h>

// 2 functions
// waterlevel_decon
// waterlevel_decon_wl

/*********************************************************************
 * This C function returns a double array that contains the
 * "peak-kept" position of water-level deconvolution:
 * decon y from x.
 *
 * Padding y and x with zeros to be the same length
 * 2*max(xnptsy,ynpts) to prevent wrap around artifacts.
 *
 * (for waterlevel_decon_wl:)
 * Differ from water_decon in the multiple waterlevels set up.
 *
 * double **x             ----  2-D array pointer x ( signal ).
 * int    xnptsx          ----  Number of traces.
 * int    xnptsy          ----  Length of each traces.
 *                              Will decon y from every traces in x.
 * double *y              ----  Source pointer.
 * int    ynpts           ----  Source length.
 * int    P1              ----  Peak position on the source.
 * int    *P2             ----  Peak positions on each traces. ( 1 * xnptsx )
 * double **deconed       ----  Deconed result, 2-D.
 *                              xnptsx * ( 2*max(xnptsy,ynpts) )
 * double waterlevel      ----  Water level. (percentage of the peak spectrum value)
 * double delta           ----  Signals and Source sampling rate.
 * int    verbose         ----  =1 : output the follwing details:
 * double *filled_amp     ----  the spectrum of zero-padded source.
 *                              1 * ( max(xnptsy,ynpts)+1 )
 * double *filled_phase   ----  the phase of zero-padded source.
 *                              1 * ( max(xnptsy,ynpts)+1 )
 * double **fft_amp       ----  the spectrum of zero-padded signal.
 *                              xnptsx * ( max(xnptsy,ynpts)+1 )
 * double **fft_phase     ----  the phase of zero-padded signal.
 *                              xnptsx * ( max(xnptsy,ynpts)+1 )
 * double **divide_amp    ----  the spectrum of divided signal.
 *                              xnptsx * ( max(xnptsy,ynpts)+1 )
 * double **divide_phase  ----  the phase of divided signal.
 *                              xnptsx * ( max(xnptsy,ynpts)+1 )
 *
 * (for waterlevel_decon_wl:)
 * double *waterlevel     ----  Water level. (percentage of the peak spectrum value)
 *
 * Note: Absolute amplitudes of the deconed traces are not normalized.
 *       The peak position is tricky, assuming the source and
 *       signal peak are aligned at their peak, then the result
 *       has the peak at the center.
 *
 * Shule Yu
 * May 07 2015
 *
 * Dependence: fftw-3.
 *
 * Key words : deconvolution, water-level
*********************************************************************/

void waterlevel_decon(double **x,int xnptsx,int xnptsy,double *y,int ynpts, int P1, int *P2, double **deconed,double waterlevel,double delta,int verbose,double *filled_amp, double *filled_phase, double **fft_amp, double **fft_phase, double **divide_amp, double **divide_phase){

    int          NPTS,count,count2,NPTS_FFT;
    double       W,*in,*esf_unfilled_amp,*esf_filled_real,*esf_filled_imag,df,*dummy_for_signal,*dummy_for_source;
    fftw_complex *out;
    fftw_plan    p1,p2;

    if ( xnptsx<1 || xnptsy<2 || ynpts<2 ){
        printf("In %s: array length too small ...\n",__func__);
        exit(1);
    }

    // Set up trace length.
    NPTS=(xnptsy>=ynpts)?(2*xnptsy):(2*ynpts);
    NPTS_FFT=NPTS/2+1;
    df=1.0/delta/NPTS;


    // Malloc space for FFT.
    esf_unfilled_amp=(double *)malloc(NPTS_FFT*sizeof(double));
    esf_filled_real=(double *)malloc(NPTS_FFT*sizeof(double));
    esf_filled_imag=(double *)malloc(NPTS_FFT*sizeof(double));
    in=(double *)malloc(NPTS*sizeof(double));
    out=(fftw_complex *)fftw_malloc(NPTS_FFT*sizeof(fftw_complex));


    // Define fft transform plan.
    p1=fftw_plan_dft_r2c_1d(NPTS,in,out,FFTW_MEASURE);
    p2=fftw_plan_dft_c2r_1d(NPTS,out,in,FFTW_MEASURE);


    // Padding with zeros.
    dummy_for_signal=(double *)malloc((NPTS-xnptsy+1)*sizeof(double));
    dummy_for_source=(double *)malloc((NPTS-ynpts+1)*sizeof(double));
    for (count=0;count<(NPTS-ynpts+1);count++){
        dummy_for_source[count]=0;
    }
    dummy_for_source[NPTS/2-P1]=1;

    convolve(y,dummy_for_source,ynpts,NPTS-ynpts+1,in);

    // Run esf fft.
    fftw_execute(p1);

    // Find max esf_unfilled_amp and waterlevel.
    for (count=0;count<NPTS_FFT;count++){
        esf_unfilled_amp[count]=sqrt(pow(out[count][0],2)+pow(out[count][1],2));
    }
    W=waterlevel*amplituded(esf_unfilled_amp,NPTS_FFT);


    // Fill with water.
    for (count=0;count<NPTS_FFT;count++){
        if ( esf_unfilled_amp[count]<W ){
            if(esf_unfilled_amp[count]>0){
                out[count][0]*=(W/esf_unfilled_amp[count]);
                out[count][1]*=(W/esf_unfilled_amp[count]);
            }
            else {
                printf("amplitude = 0 @ %.4lf Hz ..\n",count*df);
                out[count][0]=W;
                out[count][1]=0.0;
            }
        }

        esf_filled_real[count]=out[count][0];
        esf_filled_imag[count]=out[count][1];
    }


    if (verbose==1){
        // Return Time domain water-filled source.
        for (count=0;count<NPTS_FFT;count++){
            filled_amp[count]=sqrt(pow(out[count][0],2)+pow(out[count][1],2));
            filled_phase[count]=atan2(out[count][1],out[count][0]);
        }
    }


    // Decon every traces.
    for (count=0;count<xnptsx;count++){


        // Padding signal with zeros.
        for (count2=0;count2<(NPTS-xnptsy+1);count2++){
            dummy_for_signal[count2]=0;
        }

        dummy_for_signal[NPTS/2-P2[count]]=1;

        convolve(x[count],dummy_for_signal,xnptsy,NPTS-xnptsy+1,in);


        // FFT each trace.
        fftw_execute(p1);

        if (verbose==1){

            // Output zero-padded signal spectrum amplitude and phase.
            for (count2=0;count2<NPTS_FFT;count2++){
                fft_amp[count][count2]=sqrt(pow(out[count2][0],2)+pow(out[count2][1],2));
                fft_phase[count][count2]=atan2(out[count2][1],out[count2][0]);
            }
        }


        // Division.
        for (count2=0;count2<NPTS_FFT;count2++){
            complex_divide(out[count2][0],out[count2][1],esf_filled_real[count2],esf_filled_imag[count2],&out[count2][0],&out[count2][1]);
        }


        if (verbose==1){

            // Output divided signal spectrum amplitude and phase.
            for (count2=0;count2<NPTS_FFT;count2++){
                divide_amp[count][count2]=sqrt(pow(out[count2][0],2)+pow(out[count2][1],2));
                divide_phase[count][count2]=atan2(out[count2][1],out[count2][0]);
            }
        }


        // iFFT deconed traces.
        fftw_execute(p2);


        // Shift the deconed trace to the peak of signal.
        shift_array(in,NPTS,NPTS/2);
        for (count2=0;count2<NPTS;count2++){
            deconed[count][count2]=in[count2];
        }

    }

    fftw_destroy_plan(p1);
    fftw_destroy_plan(p2);
    fftw_free(out);
    free(in);
    free(dummy_for_source);
    free(dummy_for_signal);
    free(esf_unfilled_amp);
    free(esf_filled_real);
    free(esf_filled_imag);

    return;
}

void waterlevel_decon_wl(double **x,int xnptsx,int xnptsy,double *y,int ynpts, int P1, int *P2, double **deconed,double *waterlevel,double delta,int verbose,double *filled_amp, double *filled_phase, double **fft_amp, double **fft_phase, double **divide_amp, double **divide_phase){

    int          NPTS,count,count2,NPTS_FFT;
    double       W,*in,*esf_unfilled_amp,*esf_filled_real,*esf_filled_imag,df,*dummy_for_signal,*dummy_for_source,*esf_unfilled_real,*esf_unfilled_imag;
    fftw_complex *out;
    fftw_plan    p1,p2;

    if ( xnptsx<1 || xnptsy<2 || ynpts<2 ){
        printf("In %s: array length too small ...\n",__func__);
        exit(1);
    }

    // Set up trace length.
    NPTS=(xnptsy>=ynpts)?(2*xnptsy):(2*ynpts);
    NPTS_FFT=NPTS/2+1;
    df=1.0/delta/NPTS;


    // Malloc space for FFT.
    esf_unfilled_amp=(double *)malloc(NPTS_FFT*sizeof(double));
    esf_unfilled_real=(double *)malloc(NPTS_FFT*sizeof(double));
    esf_unfilled_imag=(double *)malloc(NPTS_FFT*sizeof(double));
    esf_filled_real=(double *)malloc(NPTS_FFT*sizeof(double));
    esf_filled_imag=(double *)malloc(NPTS_FFT*sizeof(double));
    in=(double *)malloc(NPTS*sizeof(double));
    out=(fftw_complex *)fftw_malloc(NPTS_FFT*sizeof(fftw_complex));


    // Define fft transform plan.
    p1=fftw_plan_dft_r2c_1d(NPTS,in,out,FFTW_MEASURE);
    p2=fftw_plan_dft_c2r_1d(NPTS,out,in,FFTW_MEASURE);


    // Padding with zeros.
    dummy_for_signal=(double *)malloc((NPTS-xnptsy+1)*sizeof(double));
    dummy_for_source=(double *)malloc((NPTS-ynpts+1)*sizeof(double));
    for (count=0;count<(NPTS-ynpts+1);count++){
        dummy_for_source[count]=0;
    }
    dummy_for_source[NPTS/2-P1]=1;
    convolve(y,dummy_for_source,ynpts,NPTS-ynpts+1,in);

    // Run esf fft.
    fftw_execute(p1);

    // Find max esf_unfilled_amp and waterlevel.
    for (count=0;count<NPTS_FFT;count++){
        esf_unfilled_real[count]=out[count][0];
        esf_unfilled_imag[count]=out[count][1];
        esf_unfilled_amp[count]=sqrt(pow(out[count][0],2)+pow(out[count][1],2));
    }


    // Decon every traces.
    for (count=0;count<xnptsx;count++){

        // Find costomized waterlevels and filled original signal with water.
        W=waterlevel[count]*amplituded(esf_unfilled_amp,NPTS_FFT);

        for (count2=0;count2<NPTS_FFT;count2++){
            if ( esf_unfilled_amp[count2]<W ){
                if(esf_unfilled_amp[count2]>0){
                    esf_filled_real[count2]=esf_unfilled_real[count2]*W/esf_unfilled_amp[count2];
                    esf_filled_imag[count2]=esf_unfilled_imag[count2]*W/esf_unfilled_amp[count2];
                }
                else {
                    printf("amplitude = 0 @ %.4lf Hz ..\n",count2*df);
                    esf_filled_real[count2]=W;
                    esf_filled_imag[count2]=0.0;
                }
            }
            else{
                esf_filled_real[count2]=esf_unfilled_real[count2];
                esf_filled_imag[count2]=esf_unfilled_imag[count2];
            }
        }


        if (verbose==1){
            // Return Time domain water-filled source.
            for (count2=0;count2<NPTS_FFT;count2++){
                filled_amp[count2]=sqrt(pow(esf_filled_real[count2],2)+pow(esf_filled_imag[count2],2));
                filled_phase[count2]=atan2(esf_filled_imag[count2],esf_filled_real[count2]);
            }
        }


        // Padding signal with zeros.
        for (count2=0;count2<(NPTS-xnptsy+1);count2++){
            dummy_for_signal[count2]=0;
        }

        dummy_for_signal[NPTS/2-P2[count]]=1;

        convolve(x[count],dummy_for_signal,xnptsy,NPTS-xnptsy+1,in);


        // FFT each trace.
        fftw_execute(p1);

        if (verbose==1){

            // Output zero-padded signal spectrum amplitude and phase.
            for (count2=0;count2<NPTS_FFT;count2++){
                fft_amp[count][count2]=sqrt(pow(out[count2][0],2)+pow(out[count2][1],2));
                fft_phase[count][count2]=atan2(out[count2][1],out[count2][0]);
            }
        }


        // Division.
        for (count2=0;count2<NPTS_FFT;count2++){
            complex_divide(out[count2][0],out[count2][1],esf_filled_real[count2],esf_filled_imag[count2],&out[count2][0],&out[count2][1]);
        }


        if (verbose==1){

            // Output divided signal spectrum amplitude and phase.
            for (count2=0;count2<NPTS_FFT;count2++){
                divide_amp[count][count2]=sqrt(pow(out[count2][0],2)+pow(out[count2][1],2));
                divide_phase[count][count2]=atan2(out[count2][1],out[count2][0]);
            }
        }


        // iFFT deconed traces.
        fftw_execute(p2);


        // Shift the deconed trace to the peak of signal.
        shift_array(in,NPTS,NPTS/2);
        for (count2=0;count2<NPTS;count2++){
            deconed[count][count2]=in[count2];
        }

    }

    fftw_destroy_plan(p1);
    fftw_destroy_plan(p2);
    fftw_free(out);
    free(in);
    free(dummy_for_source);
    free(dummy_for_signal);
    free(esf_unfilled_amp);
    free(esf_unfilled_real);
    free(esf_unfilled_imag);
    free(esf_filled_real);
    free(esf_filled_imag);

    return;
}
