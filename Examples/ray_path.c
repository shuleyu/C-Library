#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<ASU_tools.h>

int main(int argc, char **argv){

    int    NPTS,npts,flag,count;
    FILE   *fpout;
    double rayp,dh,Dmin,Dmax,dmin,dmax,*Radius,*Velocity,*deg,*radius,traveltime,traveldistance;

    Dmin=0;
    dmin=0;
    dmax=2891;
    Dmax=2892;
    dh=0.1;

    NPTS=(int)ceil((Dmax-Dmin)/dh);
    Radius=(double *)malloc(NPTS*sizeof(double));
    Velocity=(double *)malloc(NPTS*sizeof(double));
    deg=(double *)malloc(NPTS*sizeof(double));
    radius=(double *)malloc(NPTS*sizeof(double));
    for (count=0;count<NPTS;count++){
        Radius[count]=6371.0-Dmin-dh*count;
        Velocity[count]=r_vs(Radius[count]);
    }

    rayp=(6371.0-dmin)*sin(30*M_PI/180)/d_vs(dmin);

    flag=ray_path(rayp,NPTS,Radius,Velocity,dmin,dmax,89.9,&traveltime,&traveldistance,deg,radius,&npts);

    fpout=fopen("data/ray_path_out","w");
    for (count=0;count<npts;count++){
        fprintf(fpout,"%.4lf\t%.2lf\n",deg[count],radius[count]);
    }
    fclose(fpout);

    if (flag==1){
        printf("Ray turns !\n");
    }

    printf("Rayp      : %.3lf\n",rayp/180*M_PI);
    printf("TravelTime: %.3lf\n",traveltime);
    printf("Pursuit   : %.3lf\n",traveldistance);

    free(Radius);
    free(Velocity);
    free(deg);
    free(radius);

    return 0;
}
