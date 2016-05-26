#include<stdio.h>
#include<stdlib.h>
#include<ASU_tools.h>

int main(){

    int   npts,count;
    FILE  *fp;
    float *ptmp,tmpd,*p;

    fp=fopen("data/normalize_infile","r");
    npts=0;
    while (fscanf(fp,"%f",&tmpd)==1){
        npts++;
    }
    fclose(fp);

    p=(float *)malloc(npts*sizeof(float));
    fp=fopen("data/normalize_infile","r");
    ptmp=p;
    while (fscanf(fp,"%f",ptmp)==1){
        ptmp++;
    }
    fclose(fp);

    // Use function.
    printf("%lf\n",normalize(p,npts));

    // Output result.
    fp=fopen("data/normalize_out","w");
    for (count=0;count<npts;count++){
        fprintf(fp,"%.4e\n",p[count]);
    }
    fclose(fp);

    free(p);
    return 0;
}
