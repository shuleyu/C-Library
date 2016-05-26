#include<stdio.h>
#include<ASU_tools.h>

int main(){

    int    count;
    double p[4],dx,dy;

    for (count=0;count<4;count++){
        p[count]=count+1;
    }

    dx=0.957166948242946;
    dy=0.485375648722841;

    // Use function.
    printf("%.15lf\n",interp2_linear(p,dx,dy));

    return 0;
}
// Matlab Benchmark:
// x=[0,1];
// a=linspace(1,4,4);
// V=reshape(a,2,2);
// interp2(x,x,V,0.485375648722841,0.957166948242946,'linear')
