#include<stdio.h>
#include<math.h>
#include<ASU_tools.h>

int main(){

    double x,c1,c2;

    c1=-M_PI;
    c2=M_PI;

    // Use function.
    for (x=c1-1;x<c2+1;x=x+0.1){
        printf("%lf\t%lf\n",x,ramp_function(x,c1,c2));
    }

    return 0;
}
