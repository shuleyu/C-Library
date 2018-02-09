#include<stdio.h>
#include<math.h>
#include<ASU_tools.h>

/***********************************************************
 * This C function return the angle ( in rad. ) between
 * two directions given in spherical coordinates ( in rad. ).
 *
 * Theta     : angle with z, 0 <= theta <= PI.
 * Phi       : angle with x, counter-clockwise.
 *
 * double phi1    ----  \phi1.
 * double theta1  ----  \theta1.
 * double phi2    ----  \phi2.
 * double theta2  ----  \theta2.
 * Return value   ----  angle between this two directions.
 *                      (0 ~ pi)
 *
 * Shule Yu
 * Jun 16 2015
 *
 * Key words: geography, coordinates, angle.
***********************************************************/

double tpangle(double phi1, double theta1, double phi2, double theta2){

    double a1,b1,c1,a2,b2,c2;

    // Find the unit vector of direction 1.
    c1=cos(theta1);
    a1=sin(theta1);
    b1=a1*sin(phi1);
    a1*=cos(phi1);

    // Find the unit vector of direction 2.
    c2=cos(theta2);
    a2=sin(theta2);
    b2=a2*sin(phi2);
    a2*=cos(phi2);

    // Make Angle.
    return acos(a1*a2+b1*b2+c1*c2);
}
