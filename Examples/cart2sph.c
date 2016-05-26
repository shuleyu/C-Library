#include<stdio.h>
#include<math.h>
#include<ASU_tools.h>

int main(){

    double r,theta,phi;
    double x,y,z;

    x=19.12;
    y=12.3;
    z=23.34;

    // Use function.
    cart2sph(x,y,z,&r,&phi,&theta);
    printf("%.10lf\t%.10lf\t%.10lf\n",phi,theta,r);
    return 0;

}
// Matlab benchmark:
// [phi,theta,r]=cart2sph(19.12,12.3,23.34)
// theta = pi/2-theta
