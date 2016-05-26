#include<stdio.h>
#include<math.h>
#include<ASU_tools.h>

double f(double x){
    return 1/x;
}

int main(){

    double x1,x2;

    x1=1;
    x2=2;

    // Use Function.
    printf("%.10lf\n",simpsonx(f,x1,x2,1e-8));

    return 0;
}
