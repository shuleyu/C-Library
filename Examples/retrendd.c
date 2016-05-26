#include<stdio.h>
#include<stdlib.h>
#include<ASU_tools.h>

int main(){

    int    npts,count;
    FILE   *fp;
    double *ptmp,*p;

    npts=filenr("data/retrend_infile");
    p=(double *)malloc(npts*sizeof(double));

    fp=fopen("data/retrend_infile","r");
    ptmp=p;
    while (fscanf(fp,"%lf",ptmp)==1){
        ptmp++;
    }
    fclose(fp);

    // Use function.
    retrendd(0,p,1000,0.01);

    fp=fopen("data/retrend_out","w");
    for (count=0;count<npts;count++){
        fprintf(fp,"%.10lf\n",p[count]);
    }
    fclose(fp);

    return 0;
}
// SAC Benchmark:
// see retrend_matlab.m
