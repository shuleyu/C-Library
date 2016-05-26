#include<stdio.h>
#include<stdlib.h>
#include<ASU_tools.h>

int main(){

    int    npts,count;
    FILE   *fp;
    float  *ptmp,*p;

    npts=filenr("data/retrend_infile");
    p=(float *)malloc(npts*sizeof(float));

    fp=fopen("data/retrend_infile","r");
    ptmp=p;
    while (fscanf(fp,"%f",ptmp)==1){
        ptmp++;
    }
    fclose(fp);

    // Use function.
    retrend(0,p,1000,0.01);

    fp=fopen("data/retrend_out","w");
    for (count=0;count<npts;count++){
        fprintf(fp,"%.8f\n",p[count]);
    }
    fclose(fp);

    return 0;
}
// Matlab Benchmark:
// see retrend_matlab.m
