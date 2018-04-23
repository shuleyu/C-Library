#include<stdio.h>
#include<stdlib.h>
#include<ASU_tools.h>

int main(){
    double azimuth,take_off;
    double strike,dip,rake;

    azimuth=0;

    strike=0;
    dip=90;
    rake=0;

//     Auxiliary plane can be calculated at http://www.wolframalpha.com.
//     double strike2,dip2,rake2;

    // Use function.
    for (take_off=1;take_off<180;take_off+=15)
        printf("%.10lf\n",rad_pat(strike,dip,rake,azimuth,take_off,2));

    return 0;
}
