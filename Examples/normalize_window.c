#include<stdio.h>
#include<stdlib.h>
#include<ASU_tools.h>

int main(){

    int   npts,count;
    FILE  *fp;
    double *ptmp,tmpd,*p;

    fp=fopen("data/normalize_infile","r");
    npts=0;
    while (fscanf(fp,"%lf",&tmpd)==1){
        npts++;
    }
    fclose(fp);

    p=(double *)malloc(npts*sizeof(double));
    fp=fopen("data/normalize_infile","r");
    ptmp=p;
    while (fscanf(fp,"%lf",ptmp)==1){
        ptmp++;
    }
    fclose(fp);

    // Use function.
    printf("%lf\n",normalize_window(p,npts,174,1));

    // Output result.
    fp=fopen("data/normalize_window_out","w");
    for (count=0;count<npts;count++){
        fprintf(fp,"%.4e\n",p[count]);
    }
    fclose(fp);
    
    free(p);
    return 0;    
}
