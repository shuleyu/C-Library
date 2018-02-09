// Use this command instead of this function:
// taup_path -mod prem -h 500 -ph S -evt 0 0 -sta 34 53 -o stdout | grep -v ">" | sort -g -k2 |  head -n 1

#include<stdio.h>
#include<ASU_tools.h>

// Two functions:
// bottom_location
// bottom_location_fp

/***********************************************************
 * This C function calculate the bottom location of certain
 * phases ( such as P/S/ScS/PcP/ScP/PcS), using the output
 * of TauP without interpolation.
 *
 * Using TauP toolkit. Default model is PREM.
 *
 * double EVLO  ----  Event Longitude.
 * double EVLA  ----  Event Latitude.
 * double EVDP  ----  EVENT depth.
 * double STLO  ----  Station Longitude.
 * double STLA  ----  Station Latitude.
 * char   *P    ----  Chosen phase.
 * double *plo  ----  Bottom point longitude.
 * double *pla  ----  Bottom point latitude.
 * double *z    ----  Bottom point depth.
 *
 * (bottom_location_fp:)
 * double dtheta  ----  interpolate to this samping rate.
 * FILE   *fpout  ----  output file pointer.
 *
 * Shule Yu
 * Jun 06 2014
 *
 * Key words: bottoming depth, location
***********************************************************/

int bottom_location(double EVLO,double EVLA,double EVDP,double STLO,double STLA,char *P,double *plo,double *pla,double *z){

    if (EVLO>180){
        EVLO-=360;
    }
    if (STLO>180){
        STLO-=360;
    }

    char   command[200];
    FILE   *fpin;
    double Min_R,RE,theta,radius,Dist;

    RE=6371.0;
    Min_R=6371.0;

    fpin=fopen(".taup","w");
    fprintf(fpin,"taup.distance.precision=2\ntaup.depth.precision=2");
    fclose(fpin);

    sprintf(command,"taup_path -mod prem -ph %s -h %lf -deg %lf -o stdout",P,EVDP,gcpdistance(EVLO,EVLA,STLO,STLA));

    fpin=popen(command,"r");

    if (fgets(command,200,fpin)==NULL){
        fclose(fpin);
        return 1;
    }

    while (fscanf(fpin,"%lf%lf",&theta,&radius)==2){
        if (Min_R>radius){
            Min_R=radius;
            Dist=theta;
        }
    }
    pclose(fpin);

    waypoint(EVLO,EVLA,STLO,STLA,Dist,plo,pla);
    *z=RE-Min_R;
    return 0;
}

int bottom_location_fp(double EVLO,double EVLA,double EVDP,double STLO,double STLA,char *P,double *plo,double *pla,double *z, double dtheta, char *filename){

    if (EVLO>180){
        EVLO-=360;
    }
    if (STLO>180){
        STLO-=360;
    }

    char   command[200];
    FILE   *fpin,*fpout;
    double Min_R,RE,theta,radius,Dist;

    RE=6371.0;
    Min_R=6371.0;

    fpin=fopen(".taup","w");
    fprintf(fpin,"taup.distance.precision=2\ntaup.depth.precision=2");
    fclose(fpin);

    sprintf(command,"taup_path -mod prem -ph %s -h %lf -deg %lf -o stdout",P,EVDP,gcpdistance(EVLO,EVLA,STLO,STLA));

    fpin=popen(command,"r");

    if (fgets(command,200,fpin)==NULL){
        fclose(fpin);
        return 1;
    }

    fpout=fopen(filename,"w");
    while (fscanf(fpin,"%lf%lf",&theta,&radius)==2){

        if (Min_R>radius){
            Min_R=radius;
            Dist=theta;
        }

        waypoint(EVLO,EVLA,STLO,STLA,theta,plo,pla);
        fprintf(fpout,"%.2lf\t%.2lf\t%.3lf\n",*plo,*pla,RE-radius);

    }
    pclose(fpin);
    fclose(fpout);

    waypoint(EVLO,EVLA,STLO,STLA,Dist,plo,pla);
    *z=RE-Min_R;
    return 0;
}
