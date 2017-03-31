#include<stdio.h>
#include<math.h>
#include<ASU_tools.h>

int main(){

    double lon1,lat1,r1,lon2,lat2,r2,dist;

    lon1=0;
    lon2=0;
    lat1=0;
    lat2=0;
    r1=6370.0;
    r2=6371.0;

    // Use function.
    sphdist(lon1,lat1,r1,lon2,lat2,r2,&dist);
    printf("%lf\n",dist);

    return 0;    
}
