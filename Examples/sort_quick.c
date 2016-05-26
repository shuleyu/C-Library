#include<stdio.h>
#include<stdlib.h>
#include<ASU_tools.h>

int main(){

    int   npts,count;
    FILE  *fp;
    float *p,*ptmp;

    npts=filenr("data/sort_quick_infile");

    p=(float *)malloc(npts*sizeof(float));
    fp=fopen("data/sort_quick_infile","r");
    ptmp=p;
    while (fscanf(fp,"%f",ptmp)==1){
        ptmp++;
    }
    fclose(fp);

    // Use function.
    sort_quick(p,npts);

    // Output result.
    fp=fopen("data/sort_quick_out","w");
    for (count=0;count<npts;count++){
        fprintf(fp,"%f\n",p[count]);
    }
    fclose(fp);

    return 0;
}
