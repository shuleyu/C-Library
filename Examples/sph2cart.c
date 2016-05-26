#include<stdio.h>
#include<math.h>
#include<ASU_tools.h>

int main(){

    double r,theta,phi,x,y,z;

    r=1;
    theta=35*M_PI/180;
    phi=65*M_PI/180;

    // Use function.
    sph2cart(r,phi,theta,&x,&y,&z);
    printf("%.10lf\t%.10lf\t%.10lf\t%.10lf\t%.10lf\t%.10lf\n",x,y,z,r,phi*180/M_PI,theta*180/M_PI);

    return 0;
}
// Matlab Benchmark:
// r=1;
// theta=35*pi/180;
// phi=65*pi/180;
// [x,y,z]=sph2cart(phi,pi/2-theta,1)
