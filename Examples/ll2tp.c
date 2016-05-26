#include<stdio.h>
#include<math.h>
#include<ASU_tools.h>

int main(){

    int    count;
    double t,p,la,lo;

    la=40;

    // Use function.
    for (count=0;count<7222;count++){
        lo=-361+count*722.0/7220;
        ll2tp(lo,la,&p,&t);
        printf("%lf\t%lf\n",lo,p*180/M_PI);
    }

    return 0;    
}
