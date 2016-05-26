#include<stdio.h>
#include<stdlib.h>
#include<ASU_tools.h>

int main(int argc, char **argv){
    int    count;
    double a[5];

    a[0]=-1;
    a[1]=0;
    a[2]=2;
    a[3]=4;
    a[4]=8;

    // Use function.
    reverse_array(a,4);

    for (count=0;count<5;count++){
        printf("%lf\n",a[count]);
    }

    return 0;
}
