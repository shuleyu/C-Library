#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<sac.h>
#include<sacio.h>
#include<ASU_tools.h>

int main(){
    int    NPTS,count;
    FILE   *fp;
    double delta,*signal,*enveloped,begin;
    float  *signal_float,*enveloped_float;

    delta=0.025;
    begin=-5;
    NPTS=(int)ceil(2*fabs(begin)/delta);

    signal=(double *)malloc(NPTS*sizeof(double));
    enveloped=(double *)malloc(NPTS*sizeof(double));
    signal_float=(float *)malloc(NPTS*sizeof(float));
    enveloped_float=(float *)malloc(NPTS*sizeof(float));

    // Make signal.
    for (count=0;count<NPTS;count++){
//         signal[count]=(1+cos(2*M_PI*50*count*delta))*cos(2*M_PI*1000*count*delta);
        signal[count]=gaussian(-5+count*delta,1,0);
        signal_float[count]=signal[count];
    }
    normalized(signal,NPTS);
    normalize(signal_float,NPTS);

    // Use function.
    envelope_hilbert(signal,NPTS,enveloped);

    // Use sac.
    envelope(NPTS,signal_float,enveloped_float);

    // Output C.
    fp=fopen("data/envelope_hilbert_in","w");
    for (count=0;count<NPTS;count++){
        fprintf(fp,"%lf\t%lf\n",begin+count*delta,signal[count]);
    }
    fclose(fp);

    fp=fopen("data/envelope_hilbert_out","w");
    for (count=0;count<NPTS;count++){
        fprintf(fp,"%lf\t%lf\n",begin+count*delta,enveloped[count]);
    }
    fclose(fp);

    // Output SAC.
    fp=fopen("data/envelope_hilbert_sac","w");
    for (count=0;count<NPTS;count++){
        fprintf(fp,"%lf\t%f\n",begin+count*delta,enveloped_float[count]);
    }
    fclose(fp);

    // free space.
    free(signal);
    free(enveloped);
    free(signal_float);
    free(enveloped_float);

    return 0;
}
// Visualize data.
// See envelope_enveloped_matlab.m
