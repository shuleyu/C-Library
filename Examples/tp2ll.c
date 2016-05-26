#include<stdio.h>
#include<math.h>
#include<ASU_tools.h>

int main(){

    double t,p,lo,la;

    p=181*M_PI/180;
    t=91*M_PI/180;

    // Use function.
    tp2ll(p,t,&lo,&la);

    printf("%lf\n%lf\n",lo,la);

    return 0;
}
