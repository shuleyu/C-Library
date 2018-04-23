#include<stdio.h>
#include<stdlib.h>
#include<ASU_tools.h>

int main(){

    double evlo,evla,stlo,stla,dist,plo,pla;

    evlo=30;
    evla=30;

    stlo=35;
    stla=8;

    dist=5;

    // Use function.
    waypoint(evlo,evla,stlo,stla,dist,&plo,&pla);
    printf("Inputs : %lf\t%lf\t%lf\t%lf\t%lf\n",evlo,evla,stlo,stla,dist);
    printf("Outputs: %lf\t%lf\n",plo,pla);
    printf("Gcp    : %lf\t%lf\n",gcpdistance(evlo,evla,plo,pla),gcpdistance(stlo,stla,plo,pla));
    printf("Gcp_all: %lf\n",gcpdistance(evlo,evla,stlo,stla));

    return 0;
}
