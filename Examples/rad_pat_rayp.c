#include<stdio.h>
#include<stdlib.h>
#include<ASU_tools.h>

int main(){

    double evdp,rayp,az,strike,dip,rake;

    strike=244;
    dip=37;
    rake=-39;
    evdp=600;
    rayp=13.976281;
    az=78.851233;

    // Use function.
    printf("%.10lf\n",rad_pat_rayp(strike,dip,rake,az,evdp,rayp,2));

    return 0;
}
