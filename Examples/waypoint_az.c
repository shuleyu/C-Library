#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<ASU_tools.h>

int main(){

    double evlo,evla,az,dist,plo,pla;

    evlo=155.02;
    evla=-4.42;

    dist=39;
    az=60;

    // Use function.
    waypoint_az(evlo,evla,az,dist,&plo,&pla);
    printf("%.2lf\t%.2lf\n",plo,pla);

    return 0;
}
