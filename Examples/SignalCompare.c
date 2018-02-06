#include<stdio.h>
#include<stdlib.h>
#include<ASU_tools.h>

int main(){

    int   npts=8000,Peak;
	double delta=0.025,*p,*pp,*ppp;

	p=(double *)malloc(npts*sizeof(double));
	pp=(double *)malloc(npts*sizeof(double));
	ppp=(double *)malloc(npts*sizeof(double));

	gaussianfun(p,npts,delta,1);
	normalized(p,npts);
    max_ampd(p,npts,&Peak);

	StretchTrace(p,npts,Peak,1.1,0,delta,pp);
    shift_array(pp,npts,100);
	StretchTrace(p,npts,Peak,0.9,0,delta,ppp);
    shift_array(ppp,npts,-100);

	// Use function.
	int shift;
	double ccc,CCDiff,CCLDiff,Diff;
	SignalCompare(p,npts,Peak,p,npts,Peak,
	              delta,-3,3,0.25,
				  &shift,&ccc,&CCDiff,&CCLDiff,&Diff);


	//
	printf("Shift  : %.4lf\n",shift*delta);
	printf("CCC    : %.4lf\n",ccc);
	printf("CCDiff : %.8lf\n",CCDiff);
	printf("CCLDiff: %.8lf\n",CCLDiff);
	printf("Diff   : %.8lf\n\n",Diff);

	SignalCompare(p,npts,Peak,pp,npts,Peak+100,
	              delta,-3,3,0.25,
				  &shift,&ccc,&CCDiff,&CCLDiff,&Diff);

	//
	printf("Shift  : %.4lf\n",shift*delta);
	printf("CCC    : %.4lf\n",ccc);
	printf("CCDiff : %.8lf\n",CCDiff);
	printf("CCLDiff: %.8lf\n",CCLDiff);
	printf("Diff   : %.8lf\n\n",Diff);

	SignalCompare(p,npts,Peak,ppp,npts,Peak-100,
	              delta,-3,3,0.25,
				  &shift,&ccc,&CCDiff,&CCLDiff,&Diff);
	//
	printf("Shift  : %.4lf\n",shift*delta);
	printf("CCC    : %.4lf\n",ccc);
	printf("CCDiff : %.8lf\n",CCDiff);
	printf("CCLDiff: %.8lf\n",CCLDiff);
	printf("Diff   : %.8lf\n\n",Diff);

    return 0;
}
