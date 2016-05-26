#include<stdio.h>
#include<stdlib.h>
#include<ASU_tools.h>

int main(){

    int    npts;
    FILE   *fp;
    double *ptmp,*p;

    npts=filenr("data/std_infile");
    p=(double *)malloc(npts*sizeof(double));

    fp=fopen("data/std_infile","r");
    ptmp=p;
    while (fscanf(fp,"%lf",ptmp)==1){
        ptmp++;
    }
    fclose(fp);

    // Use function.
    printf("%.10lf\n",std_errd(p,npts));

    return 0;
}
// Matlab Benchmark:
// A=textread('std_err_infile');
// std(A)/sqrt(length(A))
