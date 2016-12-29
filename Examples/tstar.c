#include<stdio.h>
#include<stdlib.h>
#include<ASU_tools.h>

int main(){

    int   npts=8000,Cnt,Peak;
	double delta=0.025,ts=0.9;
	double *p;

	p=(double *)malloc(npts*sizeof(double));

    // Use function.
	tstar(delta,npts,ts,p);
	normalized(p,npts);
    max_ampd(p,npts,&Peak);

	// output.
	for (Cnt=0;Cnt<npts;++Cnt){
		printf("%.4e\t%.4e\n",(Cnt-Peak)*delta,p[Cnt]);
	}

    return 0;
}
