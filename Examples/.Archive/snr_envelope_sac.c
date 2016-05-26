
// Note: the definition of hilbert transform in SAC is
// 	     a modified version. I choose to use the original
// 	     definition of hilbert transform in deciding 
// 	     the SNR, therefore the function "snr_envelope_sac"
// 	     is deprecated.

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
        printf("%.4lf\n",snr_envelope_sac(amp[count],1000,126,375,625,250));
    }

    return 0;
}

// Matlab Demostration:
// See data/snr_envelope_matlab.m
