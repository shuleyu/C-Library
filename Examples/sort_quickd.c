#include<stdio.h>
#include<stdlib.h>
#include<ASU_tools.h>

int main(){

    int    npts,count;
    FILE   *fp;
    double *p,*ptmp;

    npts=filenr("data/sort_quick_infile");

    p=(double *)malloc(npts*sizeof(double));
    fp=fopen("data/sort_quick_infile","r");
    ptmp=p;
    while (fscanf(fp,"%lf",ptmp)==1){
        ptmp++;
    }
    fclose(fp);

    // Use function.
    sort_quickd(p,npts);

    // Output result.
    fp=fopen("data/sort_quick_out","w");
    for (count=0;count<npts;count++){
        fprintf(fp,"%lf\n",p[count]);
    }
    fclose(fp);

    return 0;
}
