#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<ASU_tools.h>

int main(){

    int    npts,count;
    FILE   *fp;
    double *p;

    npts=filenr("data/butterworth_infile");
    p=(double *)malloc(npts*sizeof(double));

    fp=fopen("data/butterworth_infile","r");
    for (count=0;count<npts;count++){
        fscanf(fp,"%lf",&p[count]);
    }
    fclose(fp);

    butterworth_bp(&p,1,npts,0.01,2,2,0.1,0.4,&p);

    // Output result.
    fp=fopen("data/butterworth_bp_C","w");
    for (count=0;count<npts;count++){
        fprintf(fp,"%.8e\n",p[count]);
    }
    fclose(fp);

    free(p);

    return 0;
}
// SAC Benchmark:
// See butterworth_matlab.m
