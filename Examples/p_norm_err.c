#include<stdio.h>
#include<math.h>
#include<ASU_tools.h>

int main(){

    double x[3],y[3];
    x[0]=0.1;
    x[1]=1.1;
    x[2]=2.1;

    y[0]=0.1;
    y[1]=2.1;
    y[2]=0.1;

    // Use function.
    printf("%.10lf\n",p_norm_err(x,y,3,2));
    return 0;
}
// matlab benchmark:
// x(1)=0.1;x(2)=1.1;x(3)=2.1;
// y(1)=0.1;y(2)=2.1;y(3)=0.1;
// norm(x-y,2)/norm(y,2)
