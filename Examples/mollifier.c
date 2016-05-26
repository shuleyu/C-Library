#include<stdio.h>
#include<ASU_tools.h>

int main(){
    double x,delta,dt;

    dt=0.1;
    delta=0.6;
    for (x=-1;x<1;x=x+dt){
        // Use Function:
        printf("%.10lf\n",mollifier(x,delta));
    }

    return 0;
}
// Matlab Benchmark
// x=-0.5
// delta=0.6;
// exp(-1/(1-(x/delta)^2))/delta
