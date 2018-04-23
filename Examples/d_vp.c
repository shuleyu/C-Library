#include<stdio.h>
#include<math.h>
#include<ASU_tools.h>

int main(){

    double Depth=300;

    printf("%.8lf\n",d_vp(Depth));
    printf("%.8lf\n",d_vs(Depth));
    printf("%.8lf\n",d_rho(Depth));

    return 0;
}
