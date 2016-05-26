#include<stdio.h>
#include<math.h>
#include<ASU_tools.h>

int main(){

    double z,colat,gcp,az,dt;
    char *P="Pdiff";

    z=310.5;
    gcp=131.5;
    colat=70;
    az=15;

    // Use function.
    if (ellipcor_kennett(P,z,colat,gcp,az,&dt)!=-1){
        printf("Ellipcity correction for %s is : %11.4lf sec.\n",P,dt);
    }

    return 0;
}
