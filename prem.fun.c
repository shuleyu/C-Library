#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<ASU_tools.h>

// 14 functions
// prem
// d_vs
// d_vp
// d_rho
// r_vs
// r_vp
// r_rho
// prem_smoothed
// d_vs_smoothed
// d_vp_smoothed
// d_rho_smoothed
// r_vs_smoothed
// r_vp_smoothed
// r_rho_smoothed

/***********************************************************
 * This C function returns PREM model values.
 *
 * double  Depth
 * int     iso    (set to 1 if want isotropy result)
 * int     ocean  (set to 1 if want ocean properties near surface)
 * double  *rho   (density)
 * dobule  *vpv
 * dobule  *vph
 * dobule  *vsv
 * dobule  *vsh
 * dobule  *qu
 * dobule  *qk
 * dobule  *yita
 *
 * Shule Yu
 * Feb 21 2014
 *
 * Key words: PREM, prem
 *
 * Reference :
 *     Physics_of_the_earth_and_planetary_interiors_1981_Dziewonski
***********************************************************/

void prem(double Depth,int iso,int ocean,double *rho,double *vpv,double *vph,double *vsv,double *vsh,double *qu,double *qk,double *yita){

    double inf=1/0.0;
    double nan=sqrt(-1);
    double R=6371.0;

    double r=R-Depth;
    double x=r/R;

    *yita=nan;
    *qk=57823;

    if ( 0<=r && r<1221.5 ) {
    // inner core

        *rho= -8.8381*pow(x,2) + 13.0885;
        *vpv= -6.3640*pow(x,2) + 11.2622;
        *vph=  *vpv;
        *vsv= -4.4475*pow(x,2) + 3.6678;
        *vsh=  *vsv;
        *qu =  84.6;
        *qk =  1327.7;
    }

    else if ( 1221.5<=r && r<3480.0 ) {
    // outter core

        *rho=  -5.5281*pow(x,3) - 3.6426*pow(x,2) - 1.2638*pow(x,1) + 12.5815;
        *vpv= -13.5732*pow(x,3) + 4.8023*pow(x,2) - 4.0362*pow(x,1) + 11.0487;
        *vph=  *vpv;
        *vsv=  0;
        *vsh=  0;
        *qu =  inf;
    }

    else if ( 3480.0<=r && r<3630.0 ) {
    // lower mantle 1

        *rho= -3.0807*pow(x,3) + 5.5283*pow(x,2) - 6.4761*pow(x,1) + 7.9565;
        *vpv= -2.5514*pow(x,3) + 5.5242*pow(x,2) - 5.3181*pow(x,1) + 15.3891;
        *vph=  *vpv;
        *vsv=  0.9783*pow(x,3) - 2.0834*pow(x,2) + 1.4672*pow(x,1) + 6.9254;
        *vsh=  *vsv;
        *qu =  312;
    }

    else if ( 3630.0<=r && r<5600.0 ) {
    // lower mantle 2

        *rho=  -3.0807*pow(x,3) +  5.5283*pow(x,2) -  6.4761*pow(x,1) +  7.9565;
        *vpv= -26.6419*pow(x,3) + 51.4832*pow(x,2) - 40.4673*pow(x,1) + 24.9520;
        *vph=  *vpv;
        *vsv=  -9.2777*pow(x,3) + 17.4575*pow(x,2) - 13.7818*pow(x,1) + 11.1671;
        *vsh=  *vsv;
        *qu =  312;
    }

    else if ( 5600.0<=r && r<5701.0 ) {
    // lower mantle 3

        *rho= -3.0807*pow(x,3) + 5.5283*pow(x,2) -  6.4761*pow(x,1) +  7.9565;
        *vpv= -2.5514*pow(x,3) + 5.5242*pow(x,2) - 23.6027*pow(x,1) + 29.2766;
        *vph=  *vpv;
        *vsv=  0.9783*pow(x,3) - 2.0834*pow(x,2) - 17.2473*pow(x,1) + 22.3459;
        *vsh=  *vsv;
        *qu =  312;
    }

    else if ( 5701.0<=r && r<5771.0 ) {
    // transition zone 1

        *rho= -1.4836*x +  5.3197;
        *vpv= -9.8672*x + 19.0957;
        *vph=  *vpv;
        *vsv= -4.9324*x +  9.9839;
        *vsh=  *vsv;
        *qu =  143;
    }

    else if ( 5771.0<=r && r<5971.0 ) {
    // transition zone 2

        *rho=  -8.0298*x + 11.2494;
        *vpv= -32.6166*x + 39.7027;
        *vph=  *vpv;
        *vsv= -18.5856*x + 22.3512;
        *vsh=  *vsv;
        *qu =  143;
    }

    else if ( 5971.0<=r && r<6151.0 ) {
    // transition zone 3

        *rho=  -3.8045*x +  7.1089;
        *vpv= -12.2569*x + 20.3926;
        *vph=  *vpv;
        *vsv=  -4.4597*x +  8.9496;
        *vsh=  *vsv;
        *qu =  143;
    }

    else if ( 6151.0<=r && r<6291.0 ) {
    // LVZ

        *rho=  0.6924*x + 2.6910;
        *vpv=  7.2180*x + 0.8317;
        *vph=  4.6172*x + 3.5908;
        *vsv= -1.4678*x + 5.8582;
        *vsh=  5.7176*x - 1.0839;
        *qu =  80;
        *yita= -2.4778*x + 3.3687;
    }

    else if ( 6291.0<=r && r<6346.6 ) {
    // LID

        *rho=  0.6924*x + 2.6910;
        *vpv=  7.2180*x + 0.8317;
        *vph=  4.6172*x + 3.5908;
        *vsv= -1.4678*x + 5.8582;
        *vsh=  5.7176*x - 1.0839;
        *qu =  600;
        *yita= -2.4778*x + 3.3687;
    }

    else if ( 6346.6<=r && r<6356.0 ) {
    // crust 1
        *rho=  2.900;
        *vpv=  6.800;
        *vph=  *vpv;
        *vsv=  3.900;
        *vsh=  *vsv;
        *qu =  600;
    }

    else if ( 6356.0<=r && r<=6371.0 ) {
    // crust 2

        *rho=  2.600;
        *vpv=  5.800;
        *vph=  *vpv;
        *vsv=  3.200;
        *vsh=  *vsv;
        *qu =  600;
    }

    else {
    // space

        printf("In %s: Depth range exceed: %.3lf !\n",__func__,R-r);

        *rho=0;
        *vpv=0;
        *vph=0;
        *vsv=0;
        *vsh=0;
        *qu = 0;
        *yita=0;

    }

    if ( ocean==1 && 6368.0<=r && r<=6371.0 ) {
    // ocean

        *rho=  1.020;
        *vpv=  1.450;
        *vph=  *vpv;
        *vsv=  0;
        *vsh=  *vsv;
        *qu =  inf;
    }

    if ( iso==1 && 6151.0<=r && r<6291.0 ) {
    // LVZ iso

        *rho=  0.6924*x + 2.6910;
        *vpv=  3.9382*x + 4.1875;
        *vph=  *vpv;
        *vsv=  2.3481*x + 2.1519;
        *vsh=  *vsv;
        *qu =  80;
        *yita= -2.4778*x + 3.3687;
    }

    if ( iso==1 && 6291.0<=r && r<6346.6 ) {
    // LID iso

        *rho=  0.6924*x + 2.6910;
        *vpv=  3.9382*x + 4.1875;
        *vph=  *vpv;
        *vsv=  2.3481*x + 2.1519;
        *vsh=  *vsv;
        *qu =  600;
        *yita= -2.4778*x + 3.3687;
    }

    return ;
}


void prem_smoothed(double Depth,double *rho,double *vpv,double *vph,double *vsv,double *vsh,double *qu,double *qk,double *yita,int RemoveCrust,int Remove220,int Remove400,int Remove670){
// Inspired from Mike Thorne.
// By default, no ocean, no anisotropy.
// Linear interpolate between +- 30km around each discontinuity.

    double r;

	r=6371.0-Depth;
    prem(Depth,1,0,rho,vpv,vph,vsv,vsh,qu,qk,yita);

	// Remove Crust.
    if ( RemoveCrust==1 && 6346.6<=r ) {
		(*vsv)=4.49100712;
		(*vpv)=8.11061727;
		(*rho)=3.38074821;
	}

	// Remove 220km.
	if ( Remove220==1 && 6121.0<=r && r<6181.0 ){
		(*vsv)=r_vs(6181.0)+(r_vs(6121.0)-r_vs(6181.0))/(6121.0-6181.0)*(r-6181.0);
		(*vpv)=r_vp(6181.0)+(r_vp(6121.0)-r_vp(6181.0))/(6121.0-6181.0)*(r-6181.0);
		(*rho)=r_rho(6181.0)+(r_rho(6121.0)-r_rho(6181.0))/(6121.0-6181.0)*(r-6181.0);
	}

	// Remove 400km.
	if ( Remove400==1 && 5941.0<=r && r<6001.0 ){
		(*vsv)=r_vs(6001.0)+(r_vs(5941.0)-r_vs(6001.0))/(5941.0-6001.0)*(r-6001.0);
		(*vpv)=r_vp(6001.0)+(r_vp(5941.0)-r_vp(6001.0))/(5941.0-6001.0)*(r-6001.0);
		(*rho)=r_rho(6001.0)+(r_rho(5941.0)-r_rho(6001.0))/(5941.0-6001.0)*(r-6001.0);
	}

	// Remove 670km.
	if ( Remove670==1 && 5671.0<=r && r<5731.0 ){
		(*vsv)=r_vs(5731.0)+(r_vs(5671.0)-r_vs(5731.0))/(5671.0-5731.0)*(r-5731.0);
		(*vpv)=r_vp(5731.0)+(r_vp(5671.0)-r_vp(5731.0))/(5671.0-5731.0)*(r-5731.0);
		(*rho)=r_rho(5731.0)+(r_rho(5671.0)-r_rho(5731.0))/(5671.0-5731.0)*(r-5731.0);
	}

	(*vsh)=(*vsv);
	(*vph)=(*vpv);

	return;
}

double d_vs(double Depth){
    double rho,vpv,vph,vsv,vsh,qu,qk,yita;
    prem(Depth,1,0,&rho,&vpv,&vph,&vsv,&vsh,&qu,&qk,&yita);
    return vsv;
}

double d_vp(double Depth){
    double rho,vpv,vph,vsv,vsh,qu,qk,yita;
    prem(Depth,1,0,&rho,&vpv,&vph,&vsv,&vsh,&qu,&qk,&yita);
    return vpv;
}

double d_rho(double Depth){
    double rho,vpv,vph,vsv,vsh,qu,qk,yita;
    prem(Depth,1,0,&rho,&vpv,&vph,&vsv,&vsh,&qu,&qk,&yita);
    return rho;
}

double r_vs(double Radius){
    double rho,vpv,vph,vsv,vsh,qu,qk,yita;
    prem(6371.0-Radius,1,0,&rho,&vpv,&vph,&vsv,&vsh,&qu,&qk,&yita);
    return vsv;
}

double r_vp(double Radius){
    double rho,vpv,vph,vsv,vsh,qu,qk,yita;
    prem(6371.0-Radius,1,0,&rho,&vpv,&vph,&vsv,&vsh,&qu,&qk,&yita);
    return vpv;
}

double r_rho(double Radius){
    double rho,vpv,vph,vsv,vsh,qu,qk,yita;
    prem(6371.0-Radius,1,0,&rho,&vpv,&vph,&vsv,&vsh,&qu,&qk,&yita);
    return rho;
}

double d_vs_smoothed(double Depth,int RemoveCrust, int Remove220, int Remove400, int Remove670){
    double rho,vpv,vph,vsv,vsh,qu,qk,yita;
    prem_smoothed(Depth,&rho,&vpv,&vph,&vsv,&vsh,&qu,&qk,&yita,RemoveCrust,Remove220,Remove400,Remove670);
    return vsv;
}

double d_vp_smoothed(double Depth,int RemoveCrust, int Remove220, int Remove400, int Remove670){
    double rho,vpv,vph,vsv,vsh,qu,qk,yita;
    prem_smoothed(Depth,&rho,&vpv,&vph,&vsv,&vsh,&qu,&qk,&yita,RemoveCrust,Remove220,Remove400,Remove670);
    return vpv;
}

double d_rho_smoothed(double Depth,int RemoveCrust, int Remove220, int Remove400, int Remove670){
    double rho,vpv,vph,vsv,vsh,qu,qk,yita;
    prem_smoothed(Depth,&rho,&vpv,&vph,&vsv,&vsh,&qu,&qk,&yita,RemoveCrust,Remove220,Remove400,Remove670);
    return rho;
}

double r_vs_smoothed(double Radius,int RemoveCrust, int Remove220, int Remove400, int Remove670){
    double rho,vpv,vph,vsv,vsh,qu,qk,yita;
    prem_smoothed(6371.0-Radius,&rho,&vpv,&vph,&vsv,&vsh,&qu,&qk,&yita,RemoveCrust,Remove220,Remove400,Remove670);
    return vsv;
}

double r_vp_smoothed(double Radius,int RemoveCrust, int Remove220, int Remove400, int Remove670){
    double rho,vpv,vph,vsv,vsh,qu,qk,yita;
    prem_smoothed(6371.0-Radius,&rho,&vpv,&vph,&vsv,&vsh,&qu,&qk,&yita,RemoveCrust,Remove220,Remove400,Remove670);
    return vpv;
}

double r_rho_smoothed(double Radius,int RemoveCrust, int Remove220, int Remove400, int Remove670){
    double rho,vpv,vph,vsv,vsh,qu,qk,yita;
    prem_smoothed(6371.0-Radius,&rho,&vpv,&vph,&vsv,&vsh,&qu,&qk,&yita,RemoveCrust,Remove220,Remove400,Remove670);
    return rho;
}
