#include<stdio.h>
#include<stdlib.h>
#include<ASU_tools.h>

int main(){

    int    npts;
    double *p,r;

    npts=10;

    p=(double *)malloc(npts*sizeof(double));

//     p[0]=9.98;
//     p[1]=10.07;
//     p[2]=9.94;
//     p[3]=10.22;
//     p[4]=9.98;
//     p[5]=10.01;
//     p[6]=10.11;
//     p[7]=10.01;
//     p[8]=9.99;
//     p[9]=9.92;

    p[0]=1.2944;
    p[1]=-0.3362;
    p[2]=1.7143;
    p[3]=2.6236;
    p[4]=0.3082;
    p[5]=1.8580;
    p[6]=2.2540;
    p[7]=-0.5937;
    p[8]=-0.4410;
    p[9]=1.5711;

        
        
        
    // Use function.
    confidence(p,npts,&r,0.95);
    printf("%.16lf\n",r);

    printf("%.16lf\n",std_d(p,npts));

    return 0;    
}
