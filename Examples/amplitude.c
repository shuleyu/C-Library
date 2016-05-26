#include<stdio.h>
#include<stdlib.h>
#include<ASU_tools.h>

int main(){

    int   npts,count;
    FILE  *fp;
    float tmpd,*p;

    // Read data.

    fp=fopen("data/amplitude_infile","r");
    npts=0;
    while (fscanf(fp,"%f",&tmpd)==1){
        npts++;
    }
    fclose(fp);

    p=(float *)malloc(npts*sizeof(float));
    fp=fopen("data/amplitude_infile","r");
    for (count=0;count<npts;count++){
        fscanf(fp,"%f",&p[count]);
    }
    fclose(fp);

    // Use function.
    printf("%lf\n",amplitude(p,npts));

    return 0;
}
