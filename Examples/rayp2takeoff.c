#include<stdio.h>
#include<math.h>
#include<ASU_tools.h>

int main(){

    double rayp,depth;

    rayp=14.640;
    depth=500;

    printf("TakeOff: %lf\n",180/M_PI*rayp2takeoff(rayp,depth,2));

    return 0;    
}
