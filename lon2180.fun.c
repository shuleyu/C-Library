// Done.

#include<stdio.h>
#include<ASU_tools.h>

/**************************************************************
 * This C function convert input longitude (deg) to [-180,180] deg.
 *
 * double lon     ----  Longitude.
 *
 * Shule Yu
 * Jan 27 2016
 *
 * Key words: coordinates, longitude.
**************************************************************/

double lon2180(double lon){

    if (lon>=0){
        lon-=360*((int)(lon/360));
    }
    else{
        lon+=360*(1+(int)(-lon/360));
    }

    if (lon>180){
        lon-=360;
    }

    return lon;
}
