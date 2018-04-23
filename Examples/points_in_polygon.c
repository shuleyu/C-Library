#include<stdio.h>
#include<stdlib.h>
#include<ASU_tools.h>

int main(){


    FILE   *fp;
    int    Cnt,*WN,npts_P,npts_L;
    double *x,*y,*xx,*yy;

    npts_P=filenr("data/points_in_polygon_points_in");
    npts_L=filenr("data/points_in_polygon_polygon_in");

    x=(double *)malloc(npts_P*sizeof(double));
    y=(double *)malloc(npts_P*sizeof(double));
    WN=(int *)malloc(npts_P*sizeof(int));
    xx=(double *)malloc(npts_L*sizeof(double));
    yy=(double *)malloc(npts_L*sizeof(double));

    fp=fopen("data/points_in_polygon_points_in","r");
    for (Cnt=0;Cnt<npts_P;Cnt++){
        fscanf(fp,"%lf%lf",x+Cnt,y+Cnt);
    }
    fclose(fp);

    fp=fopen("data/points_in_polygon_polygon_in","r");
    for (Cnt=0;Cnt<npts_L;Cnt++){
        fscanf(fp,"%lf%lf",xx+Cnt,yy+Cnt);
    }
    fclose(fp);

    // Use function.
    points_in_polygon(x,y,npts_P,xx,yy,npts_L,WN);

    for (Cnt=0;Cnt<npts_P;Cnt++){
        if (WN[Cnt]!=0) printf("(%.2lf, %.2lf) inside, winding number is %d\n",x[Cnt],y[Cnt],WN[Cnt]);
        else printf("(%.2lf, %.2lf) outside, winding number is %d\n",x[Cnt],y[Cnt],WN[Cnt]);
    }
    
    return 0;    
}
