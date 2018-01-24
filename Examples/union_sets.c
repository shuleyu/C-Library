#include<stdio.h>
#include<stdlib.h>
#include<ASU_tools.h>

int main(){

    int    npts,new_npts,count;
    double x[100],y[100];
    double xx[100],yy[100];

    npts=3;

    x[0]=-1.3;
    y[0]=-1.0;

    x[1]=-1.2;
    y[1]=-0.9;

    x[2]=-0.8;
    y[2]=-0.5;

    // Use function.
    union_sets(x,y,xx,yy,npts,&new_npts);
    printf("Before Union, npts = %d\n",npts);
    printf("Range of each sets is: \n");
    for (count=0;count<npts;count++){
        printf("%11.3lf%11.3lf\n",x[count],y[count]);
    }

    printf("\nAfter Union, npts = %d\n",new_npts);
    printf("Range of each sets is: \n");
    for (count=0;count<new_npts;count++){
        printf("%11.3lf%11.3lf\n",xx[count],yy[count]);
    }
    
    return 0;    
}
