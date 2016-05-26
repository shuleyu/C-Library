#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<ASU_tools.h>

/***********************************************************
 * This C function convert the direction of slip from
 * Strike, Dip, Rake ( in deg. ) coordinates to theta, phi
 * ( in rad. ) local coordinates. With North phi=0,
 * East phi=pi/2, South phi=pi; Up theta=0, Down theta=pi.
 *
 * Theta     : angle with up direction. 0 <= Theta <= pi.
 * Phi       : angle with north direction, 0 < Phi <= 2*pi.
 *                 i               ( phi=0 to 0 at poles. )
 *
 * double strike  ----  Strike.
 * double dip     ----  Dip.
 * double rake    ----  Rake.
 * double *phi    ----  Output \phi.
 * double *theta  ----  Output \theta.
 *
 * Shule Yu
 * Jun 16 2015
 *
 * Key words: CMT, coordinates, convertion.
***********************************************************/

void cmt2tp(double strike, double dip, double rake, double *phi, double *theta){

    // Convert to rad.
    strike*=(M_PI/180);
    dip*=(M_PI/180);
    rake*=(M_PI/180);

    // Phi direction.
    *phi=strike-atan2(tan(rake),sqrt(1+pow(tan(dip),2)));

    // Theta direction.
    *theta=M_PI/2-asin(tan(dip)*sin(rake)/sqrt(1+pow(tan(dip),2)));

    return ;
}
