#include<stdio.h>
#include<math.h>
#include<ASU_tools.h>

int main(){

    double strike,dip,rake,theta,phi;
    strike=45;
    dip=90;
    rake=-45;

    // Use function.
    cmt2tp(strike,dip,rake,&phi,&theta);
    printf("PHI: %lf\nTheta: %lf\n",phi,theta);

    return 0;    
}
