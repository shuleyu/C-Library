#include<stdio.h>
#include<string.h>
#include<ASU_tools.h>

// int main(){
//     
//     double EVLO,EVLA,EVDP,STLO,STLA,depth,plo1,pla1,plo2,pla2;
//     char   P[10];
// 
//     strcpy(P,"SKKS");
//     EVLO=0.0;
//     EVLA=0.0;
//     EVDP=200;
// 
//     STLO=120.0;
//     STLA=0.0;
// 
//     depth=2891;
// 
//     // Use function.
//     if ( waypoint_deeppath(P,EVLO,EVLA,EVDP,STLO,STLA,depth,&plo1,&pla1,&plo2,&pla2)!=0 ){
//         printf("Phase doesn't exist !\n");
//     }
//     else {
//         printf("Enter Point: %11.3lf%11.3lf\n",plo1,pla1);
//         printf("Exit Point: %11.3lf%11.3lf\n",plo2,pla2);
//     }
//     
//     return 0;    
// }

int main(){
    
    double EVLO,EVLA,EVDP,STLO,STLA,depth,plo1,pla1,plo2,pla2;
    char   P[10];

    strcpy(P,"ScS");
    EVLO=0.0;
    EVLA=0.0;
    EVDP=184.90;

    STLO=0.0;
    STLA=60.0;

    depth=2861;

    // Use function.
    if ( waypoint_deeppath(P,EVLO,EVLA,EVDP,STLO,STLA,depth,&plo1,&pla1,&plo2,&pla2) == -1 ){
        printf("Phase doesn't exist !\n");
    }
    else {
        printf("Enter Point: %11.3lf%11.3lf\n",plo1,pla1);
        printf("Exit Point: %11.3lf%11.3lf\n",plo2,pla2);
    }
    
    return 0;    
}
