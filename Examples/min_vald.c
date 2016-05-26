#include<stdio.h>
#include<stdlib.h>
#include<ASU_tools.h>

int main(){

    int    npts,pp;
    FILE   *fp;
    double *p,*ptmp,tmpd;

    fp=fopen("data/max_val_infile","r");
    npts=0;
    while (fscanf(fp,"%lf",&tmpd)==1){
        npts++;
    }
    fclose(fp);

    p=(double *)malloc(npts*sizeof(double));
    fp=fopen("data/max_val_infile","r");
    ptmp=p;
    while (fscanf(fp,"%lf",ptmp)==1){
        ptmp++;
    }
    fclose(fp);

    // Use function.
    printf("%lf\n",min_vald(p,npts,&pp));
    printf("Position: %d\n",pp);

    free(p);
    return 0;
}
