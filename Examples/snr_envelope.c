
// Note that

#include<stdio.h>
#include<sac.h>
#include<sacio.h>
#include<ASU_tools.h>

int main(){

    int    count;
    FILE   *fpin;
    double amp[4][1000];


    fpin=fopen("data/snr_envelope_infile","r");
    for (count=0;count<1000;count++){
        fscanf(fpin,"%*f%lf%lf%lf%lf",&amp[0][count],&amp[1][count],&amp[2][count],&amp[3][count]);
    }
    fclose(fpin);

    for (count=0;count<4;count++){
        printf("Trace %d: %.4lf\n",count+1,snr_envelope(amp[count],1000,126,375,625,251));
    }

    return 0;
}

// Matlab Demostration:
// See data/snr_envelope_matlab.m
