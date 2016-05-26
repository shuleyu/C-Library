#include<stdio.h>
#include<stdlib.h>
#include<ASU_tools.h>

int main(){

    int   npts,count;
    FILE  *fp;
    double *ptmp,*p;

    npts=filenr("data/normalize_infile");
    p=(double *)malloc(npts*sizeof(double));

    fp=fopen("data/normalize_infile","r");
    ptmp=p;
    while (fscanf(fp,"%lf",ptmp)==1){
        ptmp++;
    }
    fclose(fp);

    // Use function.
    printf("%lf\n",normalized(p,npts));

    // Output result.
    fp=fopen("data/normalized_out","w");
    for (count=0;count<npts;count++){
        fprintf(fp,"%.4e\n",p[count]);
    }
    fclose(fp);
    
    free(p);
    return 0;    
}
