#include<stdio.h>
#include<math.h>
#include<ASU_tools.h>

double f(double x){
    return exp(x);
}

int main(){
    
    double x1,x2,testnum;

    x1=0;
    x2=1;
    testnum=1.455322345;

    printf("%.20lf\n",binary_search(f,x1,x2,testnum,1e-15));
    
    return 0;
}

// Matlab benchmark.
// format long
// log(1.455322345)/log(exp(1))
