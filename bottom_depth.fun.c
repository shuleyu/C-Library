#include<stdio.h>
#include<ASU_tools.h>

/***********************************************************
 * Modified from bottom_location.fun.c, just return the
 * turning depth.
 *
 * This C function calculate the bottom location of certain
 * phases ( such as P/S/ScS/PcP/ScP/PcS), using the output
 * of TauP without interpolation.
 *
 * Using TauP toolkit. Default model is PREM.
 *
 * double DIST  ----  gcp distance.
 * double EVDP  ----  EVENT depth.
 * char   *P    ----  Chosen phase.
 * double *z    ----  Bottom point depth.
 *
 * Shule Yu
 * Jun 06 2014
 *
 * Key words: bottoming depth , location
***********************************************************/

int bottom_depth(double DIST,double EVDP,char *P,double *z){

    char   command[200];
    FILE   *fpin;
    double Min_R,RE,theta,radius;

    sprintf(command,"taup_path -mod prem -ph %s -h %lf -deg %lf -o stdout",P,EVDP,DIST);

    fpin=popen(command,"r");

    if (fgets(command,200,fpin)==NULL){
        return 1;
    }

    Min_R=6371.0;
    RE=6371.0;
    while (fscanf(fpin,"%lf%lf",&theta,&radius)==2){
        if (Min_R>radius){
            Min_R=radius;
        }
    }
    pclose(fpin);

    *z=RE-Min_R;
    return 0;
}
