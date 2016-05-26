#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<ASU_tools.h>

int main(){

    double gcarc,depth,gcarc_left,gcarc_right,gcarc_calc,eps,r1,r2,RE,r3,rayp1,rayp2;

    RE=6371.0;
    gcarc=64;
    depth=350;
    
    r1=RE;
    r2=RE-depth;
    r3=RE-2891.0;

    gcarc_left=0;
    gcarc_right=gcarc;
    gcarc_calc=(gcarc_left+gcarc_right)/2;

    eps=1e-3;
    rayp1=1;
    rayp2=0;

    while(fabs(rayp1-rayp2)>eps){

        gcarc_calc=gcarc-gcarc_calc;
        findrayp(&r1,&r3,&gcarc_calc,1,1,&rayp1);

        gcarc_calc=gcarc-gcarc_calc;
        findrayp(&r2,&r3,&gcarc_calc,1,1,&rayp2);
        
        if (rayp1>rayp2){
            gcarc_left=gcarc_calc;
            
        }
        else{
            gcarc_right=gcarc_calc;
        }

        gcarc_calc=(gcarc_left+gcarc_right)/2;
        
    }

    printf("RayP, RayP_Taup: %.4lf\t%.4lf\n",(rayp1+rayp2)/2,(rayp1+rayp2)/2/180*M_PI);

    return 0;
}
