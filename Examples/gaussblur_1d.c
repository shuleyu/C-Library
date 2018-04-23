#include<stdio.h>
#include<stdlib.h>
#include<ASU_tools.h>

int main(){

    int  count,N;
    FILE *fpin,*fpout1,*fpout2;
    double *time,*amp,sigma,gwidth;

    N=filenr("data/gaussblur_1d_infile");
    time=(double *)malloc(N*sizeof(double));
    amp=(double *)malloc(N*sizeof(double));

    fpin=fopen("data/gaussblur_1d_infile","r");
    for (count=0;count<N;count++){
        fscanf(fpin,"%lf%lf",&time[count],&amp[count]);
    }
    fclose(fpin);
    normalized(amp,N);

    fpout1=fopen("data/gaussblur_1d_out1","w");
    for (count=0;count<N;count++){
        fprintf(fpout1,"%.4e\n",amp[count]);
    }
    fclose(fpout1);

    sigma=1;
    gwidth=100;
    gaussblur_1d(&amp,1,N,0.025,sigma,gwidth,&amp);
    normalized(amp,N);

    fpout2=fopen("data/gaussblur_1d_out2","w");
    for (count=0;count<N;count++){
        fprintf(fpout2,"%.4e\n",amp[count]);
    }
    fclose(fpout2);

    free(time);
    free(amp);

    return 0;
}

// Matlab Benchmark:
// See data/gaussblur_1d_matlab.m
