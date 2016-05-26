// gsl version:
#include<stdio.h>
#include<gsl/gsl_sf_legendre.h>

int main(){
	
	printf("%.16e\n",gsl_sf_legendre_Plm(50,45,0.76));
	
	return 0;
}

// Old version, using legendre.fun.c:

// #include<stdio.h>
// #include<ASU_tools.h>
// 
// int main(){
// 
//     int    l,m;
//     double x;
// 
//     l=50;
//     m=45;
//     x=0.76;
// 
//     printf("P_%d^%d( %.2lf )= %.16e\n",l,m,x,legendre(l,m,x));
// 
//     return 0;    
// }
