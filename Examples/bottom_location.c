#include<stdio.h>
#include<string.h>
#include<ASU_tools.h>

int main(int argc, char **argv){
    
    double EVLO,EVLA,EVDP,STLO,STLA,PLO,PLA,Pdepth;
    char   P[10];

    strcpy(P,"ScS");
    EVLO=-67.01;
    EVLA=-24.34;
    EVDP=184.90;

    STLO=-83.66;
    STLA=42.30;

    // Use function.
    if ( bottom_location(EVLO,EVLA,EVDP,STLO,STLA,P,&PLO,&PLA,&Pdepth) == 1 ){
        printf("Phase doesn't exist !\n");
    }
    else {
        printf("Gcarc: %lf\n",gcpdistance(EVLO,EVLA,STLO,STLA));
        printf("Lon: %lf\t Lat: %lf\nDepth: %.2lf\n",PLO,PLA,Pdepth);
    }
    
    return 0;    
}
