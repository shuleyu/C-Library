// gsl version:
#include<stdio.h>
#include<gsl/gsl_cdf.h>

int main(){
	
	printf("%.16e\n",gsl_cdf_tdist_P(-0.76,2));
	
	return 0;
}

// Old version:

// #include<stdio.h>
// #include<ASU_tools.h>
// 
// int main(){
// 
//     int    n;
//     double x;
// 
//     n=2;
//     x=-0.76;
// 
//     // Use function.
//     printf("%.16e\n",student_cdf(x,n));
// 
//     return 0;    
// }

// matlab benchmark.
// tcdf(-0.76,2)
