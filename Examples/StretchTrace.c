#include<stdio.h>
#include<stdlib.h>
#include<ASU_tools.h>

int main(){

    int   npts=8000,Cnt,Peak;
	double delta=0.025,ts=0.9,*p,*pp;

	p=(double *)malloc(npts*sizeof(double));
	pp=(double *)malloc(npts*sizeof(double));
	tstar(delta,npts,ts,p);
    max_ampd(p,npts,&Peak);

	for (Cnt=0;Cnt<npts;++Cnt){
		p[Cnt]-=1000;
		p[Cnt]*=-1;
	}

    // Use function.
	StretchTrace(p,npts,Peak,1,1,delta,pp);

	// output.
	for (Cnt=0;Cnt<npts;++Cnt){
		printf("%4e\t%.4e\t%.4e\n",(Cnt-Peak)*delta,p[Cnt],pp[Cnt]);
	}

    return 0;
}
