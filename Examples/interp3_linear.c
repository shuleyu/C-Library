#include<stdio.h>
#include<ASU_tools.h>

int main(){

    int    count;
    double p[8],dx,dy,dz;

    for (count=0;count<8;count++){
        p[count]=count+1;
    }

    dx=0.957166948242946;
    dy=0.485375648722841;
    dz=0.800280468888800;

    // Use function.
    printf("%.15lf\n",interp3_linear(p,dx,dy,dz));

    return 0;
}
// Matlab Benchmark:
// x=[0,1];
// a=linspace(1,8,8);
// V=reshape(a,2,2,2);
// interp3(x,x,x,V,0.485375648722841,0.957166948242946,0.800280468888800,'linear')
