#include<stdio.h>
#include<math.h>
#include<ASU_tools.h>

int main(){

    double x,sigma=1,mu=0;

    x=sqrt(2*log(2)*sigma);

    // Use function.
    printf("%.10lf\n",gaussian(x,sigma,mu)/gaussian(0,sigma,mu));

    return 0;
}
// Matlab Benchmark:
// x=-9.1247;
// gaussmf(x,[10,0]);
