#include<stdio.h>
#include<stdlib.h>
#include<ASU_tools.h>

int main(){

    double evlo,evla,stlo,stla,dist,plo,pla;

    stlo=134.36;
    stla=-19.9336;

    evlo=-179.78;
    evla=-23.91;
    dist=11.43;

    // Use function.
    waypoint(evlo,evla,stlo,stla,dist,&plo,&pla);
    printf("Inputs : %lf\t%lf\t%lf\t%lf\t%lf\n",evlo,evla,stlo,stla,dist);
    printf("Outputs: %lf\t%lf\n",plo,pla);
    printf("Gcp    : %lf\t%lf\n",gcpdistance(evlo,evla,plo,pla),gcpdistance(stlo,stla,plo,pla));
    printf("Gcp_all: %lf\n",gcpdistance(evlo,evla,stlo,stla));

    return 0;
}
