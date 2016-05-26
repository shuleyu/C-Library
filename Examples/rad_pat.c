#include<stdio.h>
#include<stdlib.h>
#include<ASU_tools.h>

int main(){
    double azimuth,take_off;
    double strike,dip,rake,strike2,dip2,rake2;

    azimuth=326.445;
    take_off=8.2;

    strike=281;
    dip=22;
    rake=-40;

//     Auxiliary plane calculated by http://www.wolframalpha.com.
    strike2=48.88;
    dip2=76.07;
    rake2=-107.20;

    // Use function.
    printf("%.10lf\n",rad_pat(strike,dip,rake,azimuth,take_off,1));
    printf("%.10lf\n",rad_pat(strike2,dip2,rake2,azimuth,take_off,1));

    return 0;
}
