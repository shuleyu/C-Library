#include<math.h>
#include<ASU_tools.h>

/***********************************************************
 * This C function caculate the straight line distance
 * between two geographic points.
 *
 * double lon1   ----  
 * double lat1   ----  
 * double r1     ----  
 * double lon2   ----  
 * double lat2   ----  
 * double r2     ----  
 * double *dist  ----  Output \theta.
 *
 * Shule Yu
 * May 27 2015
 *
 * Key words: geography, coordinates, distance.
***********************************************************/

void sphdist(double lon1, double lat1, double r1, double lon2, double lat2, double r2, double *dist){

    double phi1,phi2,theta1,theta2,x1,y1,z1,x2,y2,z2;

    ll2tp(lon1,lat1,&phi1,&theta1);
    ll2tp(lon2,lat2,&phi2,&theta2);

    sph2cart(r1,phi1,theta1,&x1,&y1,&z1);
    sph2cart(r2,phi2,theta2,&x2,&y2,&z2);

    *dist=sqrt(pow((x1-x2),2)+pow((y1-y2),2)+pow((z1-z2),2));

    return;
}
