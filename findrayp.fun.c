#include<math.h>
#include<stdlib.h>
#include<ASU_tools.h>

// 2 functions:
// findrayp 
// findrayp_ulvz

/******************************************************************
 * This C function returns the ray-parameters of the ray path
 * connecting two set of given points. Model is PREM.
 *
 * double *r1     ----  An array of radius of the first points.
 * double *r2     ----  An array of radius of the second points.
 * double *theta  ----  Distance ( deg. ) between two points.
 *                      theta[0]=dist(r1[0],r2[0]).
 * int    NPTS    ----  Length of the input array.
 * int    Phase   ----  1 -> S-wave
 *                      0 -> P-wave
 * double *rayp   ----  Output ray parameter array.
 *
 * (for findrayp_ulvz:)
 * double dv      ----  Velocity variation.
 * double H       ----  ULVZ thickness.
 *
 * Shule Yu
 * Jun 29 2015
 *
 * Key words: rayp, Ray Parameter. PREM, ULVZ
***********************************************************/

void findrayp(double *r1, double *r2, double *theta, int NPTS, int Phase, double *rayp){

    int    Hnum,count,count2,count3,npts,flag;
    double (*v)(double);
    double *Radius,*Velocity,NPTS_Layer,LayerDepth[100],Interval[100],RE,Hinc,eps,*radius,*degree,time,distance,rayp_calc,rayp_left,rayp_right,R1,R2,degree_travel,degree_travel_prev,theta_tmp;

    eps=1e-4;

    if (Phase==1){
        v=r_vs;
    }
    else{
        v=r_vp;
    }

    // Set up the layers. ( in km. )
    // <Layer_1>             0           0.1
    // <Layer_2>             310         0.05
    // <Layer_3>             870         0.1
    // <Layer_4>             2791        0.01
    // <Layer_5>             2991        0.1
    // <Layer_6>             5049.5      0.05
    // <Layer_7>             5249.5      0.1
    // <Layer_8>             6371.0      0
    RE=6371.0;
    LayerDepth[0]=0;
    LayerDepth[1]=310;
    LayerDepth[2]=870;
    LayerDepth[3]=2791;
    LayerDepth[4]=2991;
    LayerDepth[5]=5049.5;
    LayerDepth[6]=5249.5;
    LayerDepth[7]=6371.0;

    Interval[0]=0.1;
    Interval[1]=0.05;
    Interval[2]=0.1;
    Interval[3]=0.01;
    Interval[4]=0.1;
    Interval[5]=0.05;
    Interval[6]=0.1;
    Interval[7]=0;

    NPTS_Layer=0;
    for (count=0;count<7;count++){
        NPTS_Layer+=(int)ceil((LayerDepth[count+1]-LayerDepth[count])/Interval[count]);
    }
    NPTS_Layer++;

    Radius=(double *)malloc(NPTS_Layer*sizeof(double));
    Velocity=(double *)malloc(NPTS_Layer*sizeof(double));
    radius=(double *)malloc(NPTS_Layer*sizeof(double));
    degree=(double *)malloc(NPTS_Layer*sizeof(double));

    count3=0;
    for (count=0;count<7;count++){

        Hnum=(int)ceil((LayerDepth[count+1]-LayerDepth[count])/Interval[count]);
        Hinc=1.0*(LayerDepth[count+1]-LayerDepth[count])/Hnum;

        for (count2=0;count2<Hnum;count2++){
            Radius[count3]=RE-(LayerDepth[count]+Hinc*count2);
            Velocity[count3]=v(Radius[count3]);
            count3++;
        }
    }
    Radius[count3]=0;
    Velocity[count3]=v(0);

    // Start Calculating.
    for (count=0;count<NPTS;count++){

        if (r1[count]>r2[count]){
            R1=r1[count];
            R2=r2[count];
        }
        else{
            R1=r2[count];
            R2=r1[count];
        }

        if (theta[count]<0){
            theta_tmp=-theta[count];
        }
        else{
            theta_tmp=theta[count];
        }

        rayp_left=0;
        rayp_right=2000;
        rayp_calc=(rayp_left+rayp_right)/2;

        degree_travel=0;
        flag=1;

        while (flag==1 || fabs(degree_travel-theta_tmp)>eps){

            flag=ray_path(rayp_calc,NPTS_Layer,Radius,Velocity,RE-R1,RE-R2,89.99,&time,&distance,degree,radius,&npts);

            degree_travel_prev=degree_travel;
            degree_travel=degree[npts-1];

            if ( flag==0 && fabs(degree_travel_prev-degree_travel)<eps ){
                rayp_calc=sqrt(-1);
                break;
            }

            if (flag==1 || degree_travel>theta_tmp ){
                rayp_right=rayp_calc;
            }
            else{
                rayp_left=rayp_calc;
            }

            rayp_calc=(rayp_left+rayp_right)/2;

        }

        rayp[count]=rayp_calc;
    }

    free(Radius);
    free(Velocity);
    free(radius);
    free(degree);

    return ;
}

void findrayp_ulvz(double *r1, double *r2, double *theta, int NPTS, int Phase, double *rayp, double dv, double H){

    int    Hnum,count,count2,count3,npts,flag;
    double (*v)(double);
    double *Radius,*Velocity,NPTS_Layer,LayerDepth[100],Interval[100],RE,Hinc,eps,*radius,*degree,time,distance,rayp_calc,rayp_left,rayp_right,R1,R2,degree_travel,degree_travel_prev,theta_tmp;

    eps=1e-4;

    if (Phase==1){
        v=r_vs;
    }
    else{
        v=r_vp;
    }

    // Set up the layers. ( in km. )
    // <Layer_1>             0           0.1
    // <Layer_2>             310         0.05
    // <Layer_3>             870         0.1
    // <Layer_4>             2791        0.01
    // <Layer_5>             2991        0.1
    // <Layer_6>             5049.5      0.05
    // <Layer_7>             5249.5      0.1
    // <Layer_8>             6371.0      0
    RE=6371.0;
    LayerDepth[0]=0;
    LayerDepth[1]=310;
    LayerDepth[2]=870;
    LayerDepth[3]=2791;
    LayerDepth[4]=2991;
    LayerDepth[5]=5049.5;
    LayerDepth[6]=5249.5;
    LayerDepth[7]=6371.0;

    Interval[0]=0.1;
    Interval[1]=0.05;
    Interval[2]=0.1;
    Interval[3]=0.01;
    Interval[4]=0.1;
    Interval[5]=0.05;
    Interval[6]=0.1;
    Interval[7]=0;

    NPTS_Layer=0;
    for (count=0;count<7;count++){
        NPTS_Layer+=(int)ceil((LayerDepth[count+1]-LayerDepth[count])/Interval[count]);
    }
    NPTS_Layer++;

    Radius=(double *)malloc(NPTS_Layer*sizeof(double));
    Velocity=(double *)malloc(NPTS_Layer*sizeof(double));
    radius=(double *)malloc(NPTS_Layer*sizeof(double));
    degree=(double *)malloc(NPTS_Layer*sizeof(double));

    count3=0;
    for (count=0;count<7;count++){

        Hnum=(int)ceil((LayerDepth[count+1]-LayerDepth[count])/Interval[count]);
        Hinc=1.0*(LayerDepth[count+1]-LayerDepth[count])/Hnum;

        for (count2=0;count2<Hnum;count2++){
            Radius[count3]=RE-(LayerDepth[count]+Hinc*count2);
            Velocity[count3]=v(Radius[count3]);

            if (RE-2891.0<Radius[count3] && Radius[count3]<RE-2891.0+H+eps){
                Velocity[count3]*=dv;
            }

            count3++;
        }
    }
    Radius[count3]=0;
    Velocity[count3]=v(0);

    // Start Calculating.
    for (count=0;count<NPTS;count++){

        if (r1[count]>r2[count]){
            R1=r1[count];
            R2=r2[count];
        }
        else{
            R1=r2[count];
            R2=r1[count];
        }

        if (theta[count]<0){
            theta_tmp=-theta[count];
        }
        else{
            theta_tmp=theta[count];
        }

        rayp_left=0;
        rayp_right=2000;
        rayp_calc=(rayp_left+rayp_right)/2;

        degree_travel=0;
        flag=1;

        while (flag==1 || fabs(degree_travel-theta_tmp)>eps){

            flag=ray_path(rayp_calc,NPTS_Layer,Radius,Velocity,RE-R1,RE-R2,89.99,&time,&distance,degree,radius,&npts);

            degree_travel_prev=degree_travel;
            degree_travel=degree[npts-1];

            if ( flag==0 && fabs(degree_travel_prev-degree_travel)<eps ){
                rayp_calc=sqrt(-1);
                break;
            }

            if (flag==1 || degree_travel>theta_tmp ){
                rayp_right=rayp_calc;
            }
            else{
                rayp_left=rayp_calc;
            }

            rayp_calc=(rayp_left+rayp_right)/2;

        }

        rayp[count]=rayp_calc;
    }

    free(Radius);
    free(Velocity);
    free(radius);
    free(degree);

    return ;
}
