#include<stdio.h>
#include<stdlib.h>
#include<ASU_tools.h>

int main(){

    int   npts,count;
    FILE  *fp;
    float *p;

    npts=filenr("data/taper_infile");
    p=(float *)malloc(npts*sizeof(float));

    fp=fopen("data/taper_infile","r");
    for (count=0;count<npts;count++){
        fscanf(fp,"%f",&p[count]);
    }
    fclose(fp);

    // Use function.
    taper(p,npts,0.0499);

    fp=fopen("data/taper_out","w");
    for (count=0;count<npts;count++){
        fprintf(fp,"%.8f\n",p[count]);
    }
    fclose(fp);

    return 0;
}
// SAC Benchmark:
// See taper_matlab.m
