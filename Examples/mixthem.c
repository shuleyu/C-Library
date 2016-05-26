#include<stdio.h>
#include<stdlib.h>
#include<ASU_tools.h>

int main(){

// 	double p[15]={20.0,20.0,5.0,20.0,20.0,1.0,10.0,10.0,2.0,0.98,1.00,0.02,1.00,1.20,0.05};
// 	double p[15]={20.0,20.0,25.0,25.0,20.0,10.0,100.0,1000.0,50.0,0.80,0.80,0.02,1.00,1.00,0.05};
// 	double p[15]={10.0,10.0,5.0,29.18,34.14,4.96,60.0,420.0,60.0,0.80,0.92,0.04,1.00,1.00,0.05};
// 	double p[15]={20.0,20.0,5.0,30.174,31.162,0.988,60.0,420.0,120.0,0.80,0.92,0.04,1.00,1.00,0.05};
// 	double p[15]={5.0,20.0,5.0,10.0,40.0,10.0,2.0,10.0,2.0,0.70,1.00,0.02,1.00,1.20,0.05};
	double p[3]={32.156,33.135,1.0};

	double **res;
	int    Cnt,Cnt2,Size;

	Size=mixsize(p,3);

	res=(double **)malloc(Size*sizeof(double *));
	for (Cnt=0;Cnt<Size;++Cnt){
		res[Cnt]=(double *)malloc(1*sizeof(double));
	}

    // Use function.
	mixthem(p,3,res);

	for (Cnt=0;Cnt<Size;++Cnt){
// 		printf("201500000000\t");
		for (Cnt2=0;Cnt2<1;++Cnt2){
			printf("%lf\t",res[Cnt][Cnt2]);
		}
		printf("\n");
	}


    return 0;
}
