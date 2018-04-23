#include<stdio.h>
#include<math.h>
#include<ASU_tools.h>

/******************************************************************************
 * This C function returns ray path calculation of given ray parameter.
 * Return value: if turnning happens, return 1.
 *               if no turnning, the ray path reaches the last layer(maxdepth), return 0.
 *               if mindepth<RE-r[0] || maxdepth>RE-r[NPTS-1] ||
 *                   maxdepth<mindepth , return -1.
 *
 * double rayp      ----  ray parameter. (output_of_taup * 180 / M_PI)
 * int    NPTS      ----  array length for the layers.
 * double *r        ----  layer radius array. from surface to center.
 * double *v        ----  layer velocity array for each layer radius value.
 * double mindepth  ----  depth min, where to start the ray tracing.
 * double maxdepth  ----  depth max, where to stop the ray tracing.
 * double maxangle  ----  the judegement angle for turning. ( ~ 89.9 deg )
 * double *t        ----  output: travel time.
 * double *s        ----  output: travel distance ( in km ).
 * double *degree   ----  output: ray path, angle array.
 * double *radius   ----  output: ray path, radius array.
 * int    *npts     ----  output: ray path array length.
 *
 * Shule Yu
 * Jan 21 2015
 *
 * Key words: ray path, ray tracing, layers.
 *
 * Note:
 *     Require pre-allocated space for array degree and radius, length>=NPTS.
******************************************************************************/

int ray_path(double rayp, int NPTS, double *r, double *v, double mindepth,double maxdepth, double maxangle, double *t, double *s, double *degree, double *radius, int *npts){

    int    count,P1,P2;
    double RE, deg,B,C,D,dist;

    RE=6371.0;
    maxangle=sin(maxangle*M_PI/180);

    if (maxdepth<=mindepth){
        printf("In %s: maximum depth <= minimum depth ...\n",__func__);
        return -1;
    }

    if (maxdepth>RE-r[NPTS-1]){
        printf("In %s: maximum depth greater than grid ...\n",__func__);
        return -1;
    }

    if (mindepth<RE-r[0]){
        printf("In %s: minimum depth less than grid ...\n",__func__);
        return -1;
    }

    // Locate our start Layer and end Layer.
    for (P1=0;P1<NPTS;P1++){
        if (r[P1]<=RE-mindepth){
            break;
        }
    }

    for (P2=0;P2<NPTS;P2++){
        if (r[P2]<=RE-maxdepth){
            break;
        }
    }

    // start ray tracing.
    //     B=sin(incident_angle);
    //     C=sin(takeoff);
    //     D=sin(trun_angle);

    (*t)=0;
    (*s)=0;
    deg=0;
    for (count=P1;count<P2;count++){

        B=rayp*v[count]/r[count+1];
        C=rayp*v[count]/r[count];
        D=B*sqrt(1-C*C)-sqrt(1-B*B)*C;

        // Judge turnning.
        if (B>=maxangle){
            break;
        }

        dist=r[count+1]/C*D;
        if (isnan(dist)) sphdist(0,0,r[count],asin(D)*180/M_PI,0,r[count+1],&dist);

        // Store result of this step.
        (*t)+=dist/v[count];
        (*s)+=dist;
        deg+=asin(D)*180/M_PI;
        degree[count-P1]=deg;
        radius[count-P1]=r[count+1];
    }
    (*npts)=count-P1;

    if ( count<P2 ){
        return 1;
    }
    else{
        return 0;
    }
}
