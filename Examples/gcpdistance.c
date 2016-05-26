#include<stdio.h>
#include<ASU_tools.h>

int main(){

    double lo1,la1,lo2,la2;

    lo1=-179.81;
    la1=-23.80;

    la2=-19.9336;
    lo2=134.36;

    // Use function.
    printf("%.10lf\n",gcpdistance(lo1,la1,lo2,la2));
    return 0;
}
// matlab benchmark:
// lo1=0.019999;
// la1=-10;
// lo2=23.5;
// la2=38;
// distance(la1,lo1,la2,lo2)
