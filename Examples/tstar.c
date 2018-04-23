#include<stdio.h>
#include<stdlib.h>
#include<ASU_tools.h>

int main(){

    int   npts=8000,Cnt;
    double delta=0.025,ts=0.9;
    double *p;

    p=(double *)malloc(npts*sizeof(double));

    // Use function.
    tstar(delta,npts,ts,p);
    normalized(p,npts);

    // output.
    for (Cnt=0;Cnt<npts;++Cnt){
        printf("%.12e\n",p[Cnt]);
    }

    return 0;
}
