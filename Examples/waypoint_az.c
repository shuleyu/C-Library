#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<ASU_tools.h>

int main(){

    double evlo,evla,az,dist,plo,pla;

    evlo=-71.2071;
    evla=-8.0859;

    dist=100;
    az=340;

    // Use function.
    waypoint_az(evlo,evla,az,dist,&plo,&pla);
    printf("%.2lf\t%.2lf\n",plo,pla);

    return 0;
}
