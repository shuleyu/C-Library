#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<ASU_tools.h>

int main(){
    int    NPTS,count;
    FILE   *fp;
    double delta,sigma,gwidth,*gauss,*gauss2,*amp,*phase,*freq;

    delta=0.025;
    sigma=2;
    gwidth=50;

    NPTS=2*(int)ceil(gwidth/2/delta);
    gauss=(double *)malloc(NPTS*sizeof(double));
    gauss2=(double *)malloc(NPTS*sizeof(double));
    freq=(double *)malloc((NPTS/2+1)*sizeof(double));
    amp=(double *)malloc((NPTS/2+1)*sizeof(double));
    phase=(double *)malloc((NPTS/2+1)*sizeof(double));

    // Make signal.
    gauss[0]=gaussian(-NPTS/2*delta,sigma,0);
    gauss2[0]=gaussian(-NPTS/2*delta,sigma,0);
    gauss[NPTS/2]=gaussian(0,sigma,0);
    gauss2[NPTS/2]=gaussian(0,sigma,0);
    for (count=1;count<NPTS/2;count++){
        gauss[count]=gaussian(-(NPTS/2-count)*delta,sigma,0);
        gauss[NPTS-count]=gauss[count];
        gauss2[count]=gaussian(-(NPTS/2-count)*delta,sigma,0);
        gauss2[NPTS-count]=gauss[count];
    }

    shift_array(gauss2,NPTS,(int)(5/delta));

//     for (count=0;count<NPTS;count++){
//         gauss[count]+=0.7*gauss2[count];
//     }

    normalized(gauss,NPTS);

//     reverse_array(gauss,NPTS);

    // Use function.
    freq_amp_phase(&gauss,1,NPTS,delta,freq,&amp,&phase);

    // Output.
    fp=fopen("data/freq_amp_phase_in","w");
    for (count=0;count<NPTS;count++){
        fprintf(fp,"%.16lf\t%.16lf\n",delta*(NPTS/2-count),gauss[count]);
    }
    fclose(fp);

    fp=fopen("data/freq_amp_phase_freq_AMP_Phase","w");
    for (count=0;count<NPTS/2+1;count++){
        fprintf(fp,"%lf\t%lf\t%lf\n",freq[count],amp[count],phase[count]);
    }
    fclose(fp);

    // free space.
    free(gauss);
    free(freq);
    free(amp);
    free(phase);

    return 0;
}
// Visualize data.
// See freq_amp_phase_matlab.m
