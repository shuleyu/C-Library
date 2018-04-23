#include<stdio.h>
#include<math.h>
#include<ASU_tools.h>

int main(){

    double t1,p1,t2,p2;

    p1=1*M_PI/180;
    t1=89*M_PI/180;

    p2=1*M_PI/180;
    t2=87*M_PI/180;

    // Use function.
    printf("%lf\n",tpangle(p1,t1,p2,t2)*180/M_PI);

    double la1,lo1,la2,lo2;
    tp2ll(p1,t1,&lo1,&la1);
    tp2ll(p2,t2,&lo2,&la2);

    printf("%lf\n",gcpdistance(lo1,la1,lo2,la2));


    return 0;
}
