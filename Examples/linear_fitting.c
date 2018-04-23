#include<stdio.h>
#include<stdlib.h>
#include<ASU_tools.h>

int main(){

    int    npts,count;
    FILE   *fp;
    double slope,intercept,*y,*x;

    npts=filenr("data/retrend_infile");
    x=(double *)malloc(npts*sizeof(double));
    y=(double *)malloc(npts*sizeof(double));

    fp=fopen("data/retrend_infile","r");
    for (count=0;count<npts;count++){
        fscanf(fp,"%lf",&y[count]);
        x[count]=count*0.01;
    }
    fclose(fp);

    // Use function.
    linear_fitting(x,y,npts,&slope,&intercept);

    printf("%.10lf\t%.10lf\n",slope,intercept);

    return 0;
}
// Benchmark:
// see linear_fitting.m
