#include<stdio.h>
#include<math.h>
#include<ASU_tools.h>

/***********************************************************
 * This C function convert rayparameter in Taup, event depth
 * ,phase selected to take-off angle ( in rad. ).
 *
 * double rayp     ----  Ray parameter as the output of TauP.
 * double depth    ----  Event depth.
 * int    phase    ----  1 P-wave.
 *                       other S-wave.
 * double takeoff  ----  Take off angle for this ray (in rad).
 *
 * Shule Yu
 * May 15 2014
 *
 * Key words: geography, coordinates, convertion.
***********************************************************/

double rayp2takeoff(double rayp,double depth,int phase){

    double V;

    // Deal with velocity.
    if (phase==1){
        V=d_vp(depth);
    }
    else{
        V=d_vs(depth);
    }

    return asin(V*rayp*180/M_PI/(6371.0-depth));
}
