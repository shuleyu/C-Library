#include<stdio.h>
#include<stdlib.h>
#include<ASU_tools.h>

int main(){

    int    npts,count;
    FILE   *fp;
    double tmpd,*p;

    // Read data.

    fp=fopen("data/amplitude_infile","r");
    npts=0;
    while (fscanf(fp,"%lf",&tmpd)==1){
        npts++;
    }
    fclose(fp);

    p=(double *)malloc(npts*sizeof(double));
    fp=fopen("data/amplitude_infile","r");
    for (count=0;count<npts;count++){
        fscanf(fp,"%lf",&p[count]);
    }
    fclose(fp);

    // Use function.
    printf("%lf\n",amplituded(p,npts));
    
    return 0;    
}
