#include<stdio.h>
#include<ASU_tools.h>

int main(){

    double x;

    x=-9.1247;

    // Use function.
    printf("%.10lf\n",gaussian(x,10,0));

    return 0;
}
// Matlab Benchmark:
// x=-9.1247;
// gaussmf(x,[10,0]);
