#include<stdio.h>
#include<stdlib.h>
#include<ASU_tools.h>

int main(){

    int    npts,count;
    FILE   *fp;
    double *p;

    // Read data.

    npts=filenr("data/normalize_infile");
    p=(double *)malloc(npts*sizeof(double));

    fp=fopen("data/normalize_infile","r");
    for (count=0;count<npts;count++){
        fscanf(fp,"%lf",&p[count]);
    }
    fclose(fp);

    // Use function.
    printf("%lf\n",sum_d(p,npts));

    free(p);
    
    return 0;    
}
