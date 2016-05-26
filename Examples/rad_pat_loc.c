#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>
#include<ASU_tools.h>

int main(){
    double evdp,evla,evlo,stla,stlo;
    double strike,dip,rake;
    char   phase[10];

    strike=244;
    dip=37;
    rake=-39;

    evla=-17.8;
    evlo=-178;
    evdp=600;
    stla=12;
    stlo=-87;

    strcpy(phase,"SS");

    // Use function.
    printf("%.10lf\n",rad_pat_loc(strike,dip,rake,evlo,evla,evdp,stlo,stla,phase,2));

    return 0;
}
