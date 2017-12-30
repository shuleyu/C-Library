// Done.

#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<ASU_tools.h>

/***********************************************************
 * This C function convert longitude, latitude ( in deg. )
 * coordinates to theta, phi ( in rad. ) coordinates.
 * x axis: lon=0,lat=0. y axis: lon=90,lat=0.
 * z axis: lon= ,lat=90.
 *
 * Longitude : shift to -180 < lon <= 180.
 * Latitude  : -90 <= lat <= 90.
 *
 * Theta     : angle with z axis. 0 <= Theta <= 90.
 * Phi       : angle with x axis, -PI < Phi <= PI.
 *                             ( set to 0 at poles. )
 *
 * double lon     ----  Longitude.
 * double lat     ----  Latitude.
 * double *phi    ----  Output \phi.
 * double *theta  ----  Output \theta.
 *
 * Shule Yu
 * May 15 2014
 *
 * Key words: geography, coordinates, convertion.
***********************************************************/

void ll2tp(double lon, double lat, double *phi, double *theta){

    // Deal with latitude, theta.
    if ( lat < -90 || lat > 90 ){
        printf("In %s: Ambiguous Latitude input ...\n",__func__);
        exit(1);
    }

    if (lat==90.0){
        (*theta)=0.0;
        (*phi)=0.0;
        return ;
    }
    else if(lat==-90.0){
        (*theta)=M_PI;
        (*phi)=0.0;
        return ;
    }

    (*theta)=M_PI/2-lat*M_PI/180;

    // Deal with longitude, phi.
    if (lon>=0){
        lon-=360*((int)(lon/360));
    }
    else{
        lon+=360*(1+(int)(-lon/360));
    }

    if (lon>180){
        lon-=360;
    }

    (*phi)=lon*M_PI/180;
    return;
}
