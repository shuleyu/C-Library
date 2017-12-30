// Done.

#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<ASU_tools.h>

/***********************************************************
 * This C function convert theta, phi ( in rad. ) coordinates
 * to longitude, latitude ( in deg. ) coordinates.
 * x axis: lon=0,lat=0. y axis: lon=90,lat=0.
 * z axis: lon= ,lat=90.
 *
 * Theta     : angle with z, 0 <= theta <= PI.
 * Phi       : angle with x, counter-clockwise.
 *
 * Longitude : -180 < lon <= 180. (set to 0 at poles.)
 * Latitude  : -90 <= lat <= 90.
 *
 * double theta  ----  \theta.
 * double phi    ----  \phi.
 * double *lon   ----  Output longitude.
 * double *lat   ----  Output latitude.
 *
 * Shule Yu
 * May 15 2014
 *
 * Key words: geography, coordinates, convertion.
***********************************************************/

void tp2ll(double phi, double theta, double *lon, double *lat){

    // Deal with latitude, theta.
    if ( theta > M_PI || theta < 0.0 ){
        printf("In %s: Ambiguous Theta input ...\n",__func__);
        exit(1);
    }

    if (theta==0.0){
        (*lon)=0.0;
        (*lat)=90.0;
        return;
    }
    else if (theta==M_PI){
        (*lon)=0.0;
        (*lat)=-90.0;
        return;
    }

    (*lat)=(M_PI/2-theta)*180/M_PI;

    // Deal with longitude, phi.
    if ( phi >= 0.0 ){
        phi-=2*M_PI*((int)(phi/2/M_PI));
    }
    else{
        phi+=2*M_PI*(1+(int)(-phi/2/M_PI));
    }

    if (phi>M_PI){
        phi-=2*M_PI;
    }

    (*lon)=phi*180/M_PI;
    return;
}
