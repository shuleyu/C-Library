#include<stdio.h>
#include<math.h>
#include<ASU_tools.h>

int main(){

    double x[3];
    x[0]=0.1;
    x[1]=1.1;
    x[2]=-2.1;

    // Use function.
    printf("%.10lf\n",p_norm(x,3,2));
    return 0;
}
// matlab benchmark:
// x(1)=0.1;x(2)=1.1;x(3)=2.1;
// norm(x,2)
