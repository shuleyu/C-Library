#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<ASU_tools.h>

// 3 functions
// waypoint
// waypoint_az
// waypoint_deeppath
// waypoint_sectionpath

/***********************************************************
 * (for waypoint:)
 * This C function calculate waypoint location on the great
 * circle path start from ( EVLO, EVLA ) to ( stlo, stla )
 * for certain distance. ( all parameters are in deg. )
 *
 * (for waypoint_az:)
 * This C function calculate waypoint location on the great
 * circle path start from ( EVLO, EVLA ) in the direction
 * given by azimuth centered on ( EVLO, EVLA ) for certain
 * distance. ( all parameters in deg. )
 *
 * (for waypoint_deeppath:)
 * This C function calculate waypoint location on the great
 * circle path start from ( EVLO, EVLA ) to ( stlo, stla )
 * under certain depth. If the penertrating depth of chosen
 * phase is less than given Shell depth, return -1. ( all
 * parameters are in deg. )
 *
 * (for waypoint_sectionpath:)
 * This C function calculate waypoint location on the great
 * circle path as well as depth info start from ( EVLO, EVLA )
 * to ( stlo, stla ) under certain depth. If the penertrating
 * depth of chosen phase is less than given Shell depth,
 * return -1. If the ray did penertrat the chosen depth return
 * the actual NPTS ( all parameters are in deg. )
 *
 * Note: use "TauP tool kit".
 *
 * Range of parameters:
 *     longitude : -180 ~ 180.
 *     latitude  : -90 ~ 90.
 *     distance  : 0 ~ 180.
 *     azimuth   : 0 ~ 360.
 *
 * double EVLO  ----  Event longitude. ( deg. )
 * double EVLA  ----  Event latitude. ( deg. )
 * double stlo  ----  Station Longitude. ( deg. )
 * double stla  ----  Station Latitude. ( deg. )
 * double dist  ----  GCP Length from Event to waypoint. ( deg. )
 * double *plo  ----  Waypoint logitude. ( deg. )
 * double *pla  ----  Waypoint latitude. ( deg. )
 *
 * (for waypoint_az:)
 * double az    ----  Direction, azimuth centerd on event. ( deg. )
 *
 * (for waypoint_deeppath:)
 * char   *P     ----  Phase.
 * dobule EVDP   ----  Event Depth. ( km. )
 * dobule depth  ----  Shell depth. ( km. )
 * double *plo1  ----  Enter point Longitude. ( deg. )
 * double *pla1  ----  Enter point Longitude. ( deg. )
 * double *plo2  ----  Exit point Longitude. ( deg. )
 * double *pla2  ----  Exit point Longitude. ( deg. )
 *
 * (for waypoint_sectionpath:)
 * int    npts_in  ----  Memory space of "ans" as input. ( npts_in *3 )
 * double **ans    ----  Lon/Lat/Depth ( actual NPTS * 3 )
 *
 * Shule Yu
 * Mar 20 2014
 *
 * Key words: waypoint, great circle path.
 *
 * Reference:
 *     http://en.wikipedia.org/wiki/Great-circle_navigation
***********************************************************/

void waypoint(double EVLO,double EVLA,double stlo, double stla,double dist,double *plo,double *pla){

    // Step 1. Calculate azimuth from event to station. (azimuth is centered on event)
    double x,y;
    double a,b,C;
    double az;
    a=EVLA*M_PI/180;
    b=stla*M_PI/180;
    C=(stlo-EVLO)*M_PI/180;
    y=sin(C);
    x=cos(a)*tan(b)-sin(a)*cos(C);
    az=atan2(y,x);

    // Step 2.
    // Extend great circle arc from station to event, till it cross equator at point P.
    // Calculate azimuth from P to event (or station). (azimuth is centered on P)
    double az_p;
    y=sin(az)*cos(a);
    x=sqrt(pow(cos(az),2)+pow(sin(az),2)*pow(sin(a),2));
    az_p=atan2(y,x);

    // Step 3. Calculate the great circle distance from P to event.
    double delta_p_e;
    y=tan(a);
    x=cos(az);
    delta_p_e=atan2(y,x);

    // Step 4. Calculate longitude of point P.
    double lo_p;
    y=sin(az_p)*sin(delta_p_e);
    x=cos(delta_p_e);
    lo_p=EVLO*M_PI/180-atan2(y,x); // this may have some problem.

    // Step 5. Calculate great circle distance from point P to our destination.
    double delta;
    delta=delta_p_e+dist*M_PI/180;

    // Step 6. Calculate destination's latitude.
    y=cos(az_p)*sin(delta);
    x=sqrt(pow(cos(delta),2)+pow(sin(az_p),2)*pow(sin(delta),2));
    (*pla)=atan2(y,x);
    (*pla)*=180/M_PI;

    // Step 7. Calculate estination's longitude.
    y=sin(az_p)*sin(delta);
    x=cos(delta);
    (*plo)=lo_p+atan2(y,x);
    (*plo)*=180/M_PI;

    // Step 8. Adjust longitude to -180 < plo <= 180.

    if ((*plo)>0){
        (*plo)-=360*floor((*plo+180)/360);
    }
    else{
        (*plo)-=360*ceil((*plo-180)/360);
    }

    if ((*plo)==-180.0){
        (*plo)=180.0;
    }

    return;
}

void waypoint_az(double EVLO,double EVLA,double az,double dist,double *plo,double *pla){

    // Step 1. Calculate azimuth from event to station. (azimuth is centered on event)
    double a;
    az=az*M_PI/180;
    a=EVLA*M_PI/180;

    // Step 2.
    // Extend great circle arc from station to event, till it cross equator at point P.
    // Calculate azimuth from P to event (or station). (azimuth is centered on P)
    double x,y;
    double az_p;
    y=sin(az)*cos(a);
    x=sqrt(pow(cos(az),2)+pow(sin(az),2)*pow(sin(a),2));
    az_p=atan2(y,x);

    // Step 3. Calculate the great circle distance from P to event.
    double delta_p_e;
    y=tan(a);
    x=cos(az);
    delta_p_e=atan2(y,x);

    // Step 4. Calculate longitude of point P.
    double lo_p;
    y=sin(az_p)*sin(delta_p_e);
    x=cos(delta_p_e);
    lo_p=EVLO*M_PI/180-atan2(y,x); // this may have some problem.

    // Step 5. Calculate great circle distance from point P to our destination.
    double delta;
    delta=delta_p_e+dist*M_PI/180;

    // Step 6. Calculate destination's latitude.
    y=cos(az_p)*sin(delta);
    x=sqrt(pow(cos(delta),2)+pow(sin(az_p),2)*pow(sin(delta),2));
    (*pla)=atan2(y,x);
    (*pla)*=180/M_PI;

    // Step 7. Calculate estination's longitude.
    y=sin(az_p)*sin(delta);
    x=cos(delta);
    (*plo)=lo_p+atan2(y,x);
    (*plo)*=180/M_PI;

    // Step 8. Adjust longitude to -180 < plo <= 180.

    if ((*plo)>0){
        (*plo)-=360*floor((*plo+180)/360);
    }
    else{
        (*plo)-=360*ceil((*plo-180)/360);
    }

    if ((*plo)==-180.0){
        (*plo)=180.0;
    }

    return ;
}

int waypoint_deeppath(char *P,double EVLO,double EVLA,double EVDP,double stlo,double stla,double depth,double *plo1,double *pla1,double *plo2,double *pla2){

    int    count,npts,new_npts;
    char   command[200];
    FILE   *fp;
    double RE,dtheta,theta[2000],radius[2000],*new_theta,*new_radius;

    RE=6371.0;

    fp=fopen(".taup","w");
    fprintf(fp,"taup.distance.precision=3\ntaup.depth.precision=2");
    fclose(fp);

    sprintf(command,"taup_path -mod prem -ph %s -h %lf -deg %lf -o stdout",P,EVDP,gcpdistance(EVLO,EVLA,stlo,stla));
    fp=popen(command,"r");

    if (fgets(command,200,fp)==NULL){
        pclose(fp);
        return -1;
    }

    count=0;
    while (fscanf(fp,"%lf%lf",&theta[count],&radius[count])==2){
        if (count==0 || theta[count]!=theta[count-1]){
            count++;
        }
    }
    npts=count;
    pclose(fp);

    if (min_vald(radius,npts,&count)>RE-depth){
        return -1;
    }

    new_npts=(int)ceil(theta[npts-1]/0.01)+1;
    dtheta=theta[npts-1]/(new_npts-1);

    new_theta=(double *)malloc(new_npts*sizeof(double));
    new_radius=(double *)malloc(new_npts*sizeof(double));

    new_theta[0]=0;
    for (count=1;count<new_npts;count++){
        new_theta[count]=new_theta[count-1]+dtheta;
    }

    wiginterpd(theta,radius,npts,new_theta,new_radius,new_npts,1);

    for (count=0;count<new_npts;count++){
        if (new_radius[count]<RE-depth){
            break;
        }
    }

    waypoint(EVLO,EVLA,stlo,stla,new_theta[count],plo1,pla1);

    for (count=new_npts-1;count>=0;count--){
        if (new_radius[count]<RE-depth){
            break;
        }
    }

    waypoint(EVLO,EVLA,stlo,stla,new_theta[count],plo2,pla2);

    free(new_theta);
    free(new_radius);

    return 0;
}

int waypoint_sectionpath(char *P,double EVLO,double EVLA,double EVDP,double stlo,double stla,double depth,int npts_in,double **ans){

    int    count,npts,new_npts,StartPoint,EndPoint;
    char   command[200];
    FILE   *fp;
    double RE,dtheta,theta[2000],radius[2000],*new_theta,*new_radius,gcarc;

	gcarc=gcpdistance(EVLO,EVLA,stlo,stla);
    new_npts=(int)ceil(gcarc/0.01)+1;

	if (new_npts>npts_in){
        printf("In %s: Malloced memory too small ...\n",__func__);
		return -2;
	}

    RE=6371.0;

	// TauP
    fp=fopen(".taup","w");
    fprintf(fp,"taup.distance.precision=3\ntaup.depth.precision=2");
    fclose(fp);

    sprintf(command,"taup_path -mod prem -ph %s -h %lf -deg %lf -o stdout",P,EVDP,gcarc);

    fp=popen(command,"r");
    if (fgets(command,200,fp)==NULL){
        pclose(fp);
        return -1;
    }

    count=0;
    while (fscanf(fp,"%lf%lf",&theta[count],&radius[count])==2){
        if (count==0 || theta[count]!=theta[count-1]){
            count++;
        }
    }
    npts=count;
    pclose(fp);

	// No penertration.
    if (min_vald(radius,npts,&count)>RE-depth){
        return -1;
    }

	// With penertration.
    dtheta=theta[npts-1]/(new_npts-1);

    new_theta=(double *)malloc(new_npts*sizeof(double));
    new_radius=(double *)malloc(new_npts*sizeof(double));

    for (count=0;count<new_npts;count++){
        new_theta[count]=count*dtheta;
    }

    wiginterpd(theta,radius,npts,new_theta,new_radius,new_npts,1);

	// Find the lon/lat/depth on the path beneath depth.
    StartPoint=0;
    EndPoint=new_npts;

    for (count=0;count<new_npts;count++){
        if (new_radius[count]<RE-depth){
			StartPoint=count;
            break;
        }
    }

    for (count=new_npts-1;count>=0;count--){
        if (new_radius[count]<RE-depth){
			EndPoint=count;
            break;
        }
    }

	for (count=StartPoint;count<=EndPoint;count++){
		waypoint(EVLO,EVLA,stlo,stla,new_theta[count],&ans[count-StartPoint][0],&ans[count-StartPoint][1]);
		ans[count-StartPoint][2]=RE-new_radius[count];
	}

    free(new_theta);
    free(new_radius);

    return EndPoint-StartPoint+1;
}

