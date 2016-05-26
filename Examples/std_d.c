#include<stdio.h>
#include<stdlib.h>
#include<ASU_tools.h>

int main(){

    int    npts;
    FILE   *fp;
    double *ptmp,tmpd,*p;

    fp=fopen("data/std_infile","r");
    npts=0;
    while (fscanf(fp,"%lf",&tmpd)==1){
        npts++;
    }
    fclose(fp);

    p=(double *)malloc(npts*sizeof(double));
    fp=fopen("data/std_infile","r");
    ptmp=p;
    while (fscanf(fp,"%lf",ptmp)==1){
        ptmp++;
    }
    fclose(fp);

    // Use function.
    printf("%.12lf\n",std_d(p,npts));
    
    return 0;    
}
// matlab benchmark:
// A=textread('std_infile');
// std(A)
