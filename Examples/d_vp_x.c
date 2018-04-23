#include<stdio.h>
#include<math.h>
#include<ASU_tools.h>

int main(){

    double Depth=300;

    printf("%.8lf\n",d_vp_x(Depth));
    printf("%.8lf\n",d_vs_x(Depth));
    printf("%.8lf\n",d_rho_x(Depth));

    return 0;
}
