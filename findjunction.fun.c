#include<stdlib.h>
#include<math.h>
#include<ASU_tools.h>

/***********************************************************
 * This C function returns the junction piont of two input
 * sample points set. x1,y1 and x2,y2.
 *
 * Will use interpolated curves to find the junction point.
 *
 * x1, y1, x2, y2 is monotonous increasing or decreasing.
 *
 * double *x1    ----  Curve 1, x value.
 * double *y1    ----  Curve 1, y value.
 * int    npts1  ----  Curve 1, npts.
 * double *x2    ----  Curve 2, x value.
 * double *y2    ----  Curve 2, y value.
 * int    npts2  ----  Curve 2, npts.
 * double tol    ----  tolerance.
 * double *x     ----  junction point x value.
 * double *y     ----  junction point y value.
 *
 * If there is not junction piont, return 1.
 *
 * Shule Yu
 * Aug 13 2014
 *
 * Key words: junction.
***********************************************************/

int findjunction(double *x1,double *y1,int npts1,double *x2,double *y2,int npts2,double tol,double *x,double *y){
    int    count,npts,P;
    double lower,upper,minlow,maxup,dx,diff,err;
    double *xx1,*yy1,*xx2,*yy2,*newx,*newy1,*newy2;

    if (npts1<2 || npts2<2){
        return 1;
    }

    if (fmax(x1[0],x1[npts1-1])<=fmin(x2[0],x2[npts2-1]) && fmax(x2[0],x2[npts2-1])<=fmin(x1[0],x1[npts1-1])){
        return 1;
    }
    if (fmax(y1[0],y1[npts1-1])<=fmin(y2[0],y2[npts2-1]) && fmax(y2[0],y2[npts2-1])<=fmin(y1[0],y1[npts1-1])){
        return 1;
    }

    // Copy input array into xx1,yy1,xx2,yy2.
    xx1=(double *)malloc(npts1*sizeof(double));
    yy1=(double *)malloc(npts1*sizeof(double));
    xx2=(double *)malloc(npts2*sizeof(double));
    yy2=(double *)malloc(npts2*sizeof(double));
    if (x1[npts1-1]<x1[0]){
        for (count=0;count<npts1;count++){
            xx1[count]=x1[npts1-1-count];
            yy1[count]=y1[npts1-1-count];
        }
    }
    else{
        for (count=0;count<npts1;count++){
            xx1[count]=x1[count];
            yy1[count]=y1[count];
        }
    }
    if (x2[npts2-1]<x2[0]){
        for (count=0;count<npts2;count++){
            xx2[count]=x2[npts2-1-count];
            yy2[count]=y2[npts2-1-count];
        }
    }
    else{
        for (count=0;count<npts2;count++){
            xx2[count]=x2[count];
            yy2[count]=y2[count];
        }
    }

    // find interpolate begin/end.
    lower=fmax(xx1[0],xx2[0]);
    upper=fmin(xx1[npts1-1],xx2[npts2-1]);
    minlow=fmin(xx1[0],xx2[0]);
    maxup=fmax(xx1[npts1-1],xx2[npts2-1]);
    newx=NULL;
    newy1=NULL;
    newy2=NULL;

    npts=1000;
    err=tol+1;
    while (err>tol){
        err=tol+1;
        npts*=2;
        if (npts>100000){
            break;
        }
        free(newx);
        free(newy1);
        free(newy2);
        newx=(double *)malloc(npts*sizeof(double));
        newy1=(double *)malloc(npts*sizeof(double));
        newy2=(double *)malloc(npts*sizeof(double));
        dx=(maxup-minlow)/(npts-1);
        for (count=0;count<npts;count++){
            newx[count]=minlow+dx*count;
        }
        wiginterpd(xx1,yy1,npts1,newx,newy1,npts,1);
        wiginterpd(xx2,yy2,npts2,newx,newy2,npts,1);

        // find junction point.
        for (count=0;count<npts;count++){
            if(newx[count]>lower && newx[count]<upper){
                diff=fabs(newy1[count]-newy2[count]);
                if (err>diff){
                    err=diff;
                    P=count;
                }
            }
        }
    }
    if (err>=tol){
        free(newx);
        free(newy1);
        free(newy2);
        free(xx1);
        free(xx2);
        free(yy1);
        free(yy2);
        return 1;
    }
    else{
        (*x)=newx[P];
        (*y)=(newy1[P]+newy2[P])/2;
        free(newx);
        free(newy1);
        free(newy2);
        free(xx1);
        free(xx2);
        free(yy1);
        free(yy2);
        return 0;
    }
}
