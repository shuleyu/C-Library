#include<stdio.h>
#include<stdlib.h>
#include<ASU_tools.h>

int main(){

    double evlo,evla,stlo,stla,dist,plo,pla;

    evlo=-178.09;
	evla=-30.22;

	stlo=39.4188;
	stla=8.9285;

    dist=21.73;

    // Use function.
    waypoint(evlo,evla,stlo,stla,dist,&plo,&pla);
    printf("Inputs : %lf\t%lf\t%lf\t%lf\t%lf\n",evlo,evla,stlo,stla,dist);
    printf("Outputs: %lf\t%lf\n",plo,pla);
    printf("Gcp    : %lf\t%lf\n",gcpdistance(evlo,evla,plo,pla),gcpdistance(stlo,stla,plo,pla));
    printf("Gcp_all: %lf\n",gcpdistance(evlo,evla,stlo,stla));

    return 0;
}
