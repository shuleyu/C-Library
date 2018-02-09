#include<stdio.h>
#include<ASU_tools.h>

/***********************************************************
 * This C function convert input longitude (deg) to [0,360] deg.
 *
 * double lon     ----  Longitude.
 *
 * Shule Yu
 * Jan 27 2016
 *
 * Key words: coordinates, longitude.
***********************************************************/

double lon2360(double lon){

    if (lon>=0){
        lon-=360.0*((int)(lon/360));
    }
    else{
        lon+=360.0*(1+(int)(-lon/360));
    }

    if (lon>=360.0){
        lon=0;
    }

    return lon;
}
