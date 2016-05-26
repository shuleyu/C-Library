#include<stdio.h>
#include<stdlib.h>
#include<ASU_tools.h>

int main(){

    int    npts,count;
    FILE   *fp;
    double tmpd,*p;

    // Read data.

    fp=fopen("data/pick_onset_infile1","r");
    npts=0;
    while (fscanf(fp,"%*f%lf",&tmpd)==1){
        npts++;
    }
    fclose(fp);

    p=(double *)malloc(npts*sizeof(double));
    fp=fopen("data/pick_onset_infile1","r");
    for (count=0;count<npts;count++){
        fscanf(fp,"%*f%lf",&p[count]);
    }
    fclose(fp);

    // Use function.
    printf("%d\n",pick_onset(p,npts,0.025,11400,1200));
    
    return 0;    
}
