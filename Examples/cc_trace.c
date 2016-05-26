#include<stdio.h>
#include<stdlib.h>
#include<ASU_tools.h>

int main(){

    int    npts,count,shift;
    double *p,*result,CCC;

    npts=3;

    p=(double *)malloc(npts*sizeof(double));
    result=(double *)malloc((2*npts-1)*sizeof(double));
    p[0]=2;
    p[1]=3;
    p[2]=1;

    // Use function.
    CC_trace(p,npts,p,npts,&shift,&CCC,result);

    for (count=0;count<2*npts-1;count++){
        printf("%11.3lf\t",result[count]);
    }
    printf("\n");

    return 0;
}
