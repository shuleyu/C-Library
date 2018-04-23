#include<stdio.h>
#include<ASU_tools.h>

int main(){

    double Lon=-361.2,dl=0.2;

    // Use function.
    while (Lon<361.2){
        printf("%.16lf\t%.16lf\n",Lon,lon2360(Lon));
        Lon+=dl;
    }

    return 0;    
}
