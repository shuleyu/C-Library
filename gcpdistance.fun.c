#include<math.h>
#include<ASU_tools.h>

/***********************************************************
 * This C function returns distance (in deg) of two
 * geographic locations.
 *
 * ( in deg )
 * double lo1  ----  longitude of point 1
 * double la1  ----  latitude  of point 1
 * double lo2  ----  longitude of point 2
 * double la2  ----  latitude  of point 2
 *
 * Shule Yu
 * Mar 10 2014
 *
 * Key words: great circle path, gcp, distance.
 *
 * Reference:
 *     http://en.wikipedia.org/wiki/Great-circle_distance
***********************************************************/

double gcpdistance(double lo1,double la1, double lo2,double la2){

    double a,b,C,x,y;

    a=la1*M_PI/180;
    b=la2*M_PI/180;
    C=(lo1-lo2)*M_PI/180;

    y=sqrt(pow((cos(a)*sin(b)-sin(a)*cos(b)*cos(C)),2)+pow(cos(b)*sin(C),2));
    x=sin(a)*sin(b)+cos(a)*cos(b)*cos(C);

    return 180/M_PI*atan2(y,x);
}
