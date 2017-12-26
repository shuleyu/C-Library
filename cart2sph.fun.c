// Done.

#include<math.h>
#include<ASU_tools.h>

/***********************************************************
 * This C function convert x, y, z in Cartesian coordinates
 * to r, theta, phi ( in rad. ) in Sherical coordinates.
 *
 * double x       ----  x
 * double y       ----  y
 * double z       ----  z
 * double *r      ----  r
 * double *phi    ----  phi, angle with positive z direction. (rad)
 * double *theta  ----  theta, angle with positive x direction.  (rad)
 *
 * Shule Yu
 * May 15 2014
 *
 * Key words: coordinates, convertion, spherical, cartesian
***********************************************************/

void cart2sph(double x, double y, double z, double *r, double *phi, double *theta){

    (*r)=sqrt(pow(x,2)+pow(y,2)+pow(z,2));
    (*phi)=atan2(y,x);
    (*theta)=atan2(sqrt(pow(x,2)+pow(y,2)),z);

    return;
}
