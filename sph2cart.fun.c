// Done.

#include<math.h>
#include<ASU_tools.h>

/***********************************************************
 * This C function convert r, theta, phi ( in rad. ) in
 * Sherical coordinates to x, y, z in Cartesian coordinates.
 *
 * Theta     : angle with z axis.
 * Phi       : angle with x axis. counter-clockwise.
 *
 * double r      ----  Radius.
 * double phi    ----  \phi.
 * double theta  ----  \theta.
 * double *x     ----  Output x.
 * double *y     ----  Output y.
 * double *z     ----  Output z.
 *
 * Shule Yu
 * May 15 2014
 *
 * Key words: coordinates, convertion, spherical, cartesian
***********************************************************/

void sph2cart(double r, double phi, double theta, double *x, double *y, double *z){

    (*x)=r*cos(phi)*sin(theta);
    (*y)=r*sin(phi)*sin(theta);
    (*z)=r*cos(theta);

    return;
}
