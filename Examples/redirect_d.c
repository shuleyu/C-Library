#include<stdio.h>
#include<stdlib.h>
#include<ASU_tools.h>

int main(){

    int    nx=2,ny=5,Cnt;
    double p[10]={0,1,2,3,4,5,6,7,8,9};
    double pp[10];


    printf("Original Ordering: ");
    for (Cnt=0;Cnt<nx*ny;Cnt++){
        printf("%.2lf\t",p[Cnt]);
    }
    printf("\n");

    // Use function.
    redirect_d(p,2,5,pp);

    printf("Re-directed Ordering: ");
    for (Cnt=0;Cnt<nx*ny;Cnt++){
        printf("%.2lf\t",pp[Cnt]);
    }
    printf("\n");

    return 0;
}
