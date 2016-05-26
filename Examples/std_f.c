#include<stdio.h>
#include<stdlib.h>
#include<ASU_tools.h>

int main(){

    int   npts;
    FILE  *fp;
    float *ptmp,tmpd,*p;

    fp=fopen("data/std_infile","r");
    npts=0;
    while (fscanf(fp,"%f",&tmpd)==1){
        npts++;
    }
    fclose(fp);

    p=(float *)malloc(npts*sizeof(float));
    fp=fopen("data/std_infile","r");
    ptmp=p;
    while (fscanf(fp,"%f",ptmp)==1){
        ptmp++;
    }
    fclose(fp);

    // Use function.
    printf("%.8lf\n",std_f(p,npts));
    
    return 0;    
}
// matlab benchmark:
// A=textread('std_infile');
// std(A)
