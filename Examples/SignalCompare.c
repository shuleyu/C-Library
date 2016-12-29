#include<stdio.h>
#include<stdlib.h>
#include<ASU_tools.h>

int main(){

    int   npts=8000,Peak;
	double delta=0.025,*p,*pp,*ppp;

	p=(double *)malloc(npts*sizeof(double));
	pp=(double *)malloc(npts*sizeof(double));
	ppp=(double *)malloc(npts*sizeof(double));

	gaussianfun(p,npts,delta,1,0);
	normalized(p,npts);
    max_ampd(p,npts,&Peak);

	StretchTrace(p,npts,Peak,1.1,0,delta,pp);
	StretchTrace(p,npts,Peak,0.9,0,delta,ppp);

	// Use function.
	int shift;
	double ccc,CCDiff,Diff;
	SignalCompare(p,npts,Peak,p,npts,Peak,
	              delta,-3,3,0.1,
				  &shift,&ccc,&CCDiff,&Diff);


	//
	printf("Shift  : %.4lf\n",shift*delta);
	printf("CCC    : %.4lf\n",ccc);
	printf("CCDiff : %.2lf\n",CCDiff);
	printf("Diff   : %.2lf\n",Diff);

	SignalCompare(p,npts,Peak,pp,npts,Peak,
	              delta,-3,3,0.1,
				  &shift,&ccc,&CCDiff,&Diff);

	//
	printf("Shift  : %.4lf\n",shift*delta);
	printf("CCC    : %.4lf\n",ccc);
	printf("CCDiff : %.2lf\n",CCDiff);
	printf("Diff   : %.2lf\n",Diff);

	SignalCompare(p,npts,Peak,ppp,npts,Peak,
	              delta,-3,3,0.1,
				  &shift,&ccc,&CCDiff,&Diff);
	//
	printf("Shift  : %.4lf\n",shift*delta);
	printf("CCC    : %.4lf\n",ccc);
	printf("CCDiff : %.2lf\n",CCDiff);
	printf("Diff   : %.2lf\n",Diff);

    return 0;
}
