#include<stdio.h>
#include<stdlib.h>
#include<ASU_tools.h>

int main(){

    int    npts,count;
    FILE   *fp;
    double *p,*w;
	char   *infile="data/std_weight_infile";
// 	char   *infile="data/std_weight1.0_infile";

    npts=filenr(infile);
    p=(double *)malloc(npts*sizeof(double));
    w=(double *)malloc(npts*sizeof(double));

    fp=fopen(infile,"r");
    count=0;
    while (fscanf(fp,"%lf%lf",&p[count],&w[count])==2){
        count++;
    }
    fclose(fp);

    // Use function.
    printf("%.12lf\n",std_weight(p,w,npts));

    free(p);
    free(w);
    
    return 0;    
}
// matlab benchmark:
// A=textread('std_weight_infile');
// sqrt(var(A(:,1),abs(A(:,2))))
