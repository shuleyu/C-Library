#include<stdio.h>
#include<gsl/gsl_sf_gamma.h>

int main(){
	
	double m,n;

	m=3.423;
	n=2.423;

	printf("%.10lf\n",gsl_sf_beta(m,n));
	
	return 0;
}

// Old version, use beta.fun.c:

// #include<stdio.h>
// #include<math.h>
// #include<ASU_tools.h>
// 
// // Set tolerance to 1e-8 for short calculation time.
// int main(){
// 
//     double m,n;
// 
//     m=3.423;
//     n=2.423;
// 
//     printf("%.10lf\n",beta(m,n,1e-8));
//     return 0;
// }

// Matlab version:

// beta(m,n)
