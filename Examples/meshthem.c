#include<stdio.h>
#include<stdlib.h>
#include<ASU_tools.h>

int main(){

	int    NPTS,Cnt;
	double *res,delta;

    // Use function mode 0.
	NPTS=meshsize(0,15,0.05,0);
	res=(double *)malloc(NPTS*sizeof(double));
	delta=meshthem(res,NPTS,0,15,0.05,0);


    // Use function mode 1.
// 	NPTS=meshsize(1,2,0.5,1);
// 	res=(double *)malloc(NPTS*sizeof(double));
// 	delta=meshthem(res,NPTS,1,2,0.5,1);


    // Use function mode 2.
// 	NPTS=13;
// 	res=(double *)malloc(NPTS*sizeof(double));
// 	delta=meshthem(res,NPTS,1,2.1,0.5,2);


	for (Cnt=0;Cnt<NPTS;Cnt++){
		printf("%lf\n",res[Cnt]);
	}

	printf("Delta: %lf\nNPTS:  %d\n",delta,NPTS);

    return 0;
}
