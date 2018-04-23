#include<stdio.h>
#include<stdlib.h>
#include<ASU_tools.h>

int main(){
    int count;
    double a[5],b[2],c[6];
    a[0]=1;a[1]=2;a[2]=3;a[3]=4;a[4]=5;
    b[0]=1;b[1]=2;//b[2]=1;b[3]=0;b[4]=0;b[5]=0;

    // Use function.
    convolve(a,b,5,2,c);

    printf("A:  ");
    for (count=0;count<5;count++){
        printf("%lf\t",a[count]);
    }
    printf("\n");

    printf("B:  ");
    for (count=0;count<2;count++){
        printf("%lf\t",b[count]);
    }
    printf("\n");

    printf("C:  ");
    for (count=0;count<6;count++){
        printf("%lf\t",c[count]);
    }
    printf("\n");

    return 0;
}

// Matlab Benchmark:
// a=[1,1,1,1,1];
// b=[1,7,1,-3,1];
// conv(a,b)
