#include<stdio.h>
#include<string.h>
#include<ASU_tools.h>

int main(int argc, char **argv){
    
    double DIST,EVDP,Pdepth;
    char   P[10];

    strcpy(P,"S");
	DIST=60;
	EVDP=500;

    // Use function.
    if ( bottom_depth(DIST,EVDP,P,&Pdepth) != 0 ){
        printf("Phase doesn't exist !\n");
    }
    else {
        printf("Gcarc: %lf\n",DIST);
        printf("Depth: %.2lf km\n",Pdepth);
    }
    
    return 0;    
}
