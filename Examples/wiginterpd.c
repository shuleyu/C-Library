#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<ASU_tools.h>

int main(){

    int    npts,NPTS,count;
    FILE   *fp;
    double *p,*q,*pp,*qq,dt;

	npts=filenr("data/wiginterpd_infile");

    p=(double *)malloc(npts*sizeof(double));
    q=(double *)malloc(npts*sizeof(double));

    fp=fopen("data/wiginterpd_infile","r");
	for (count=0;count<npts;count++){
        p[count]=count*0.01;
    	fscanf(fp,"%lf",&q[count]);
    }
    fclose(fp);

    // Make targe data.
	dt=0.002;

    NPTS=1+(int)ceil((p[npts-1]-p[0])/dt);
    pp=(double *)malloc(NPTS*sizeof(double));
    qq=(double *)malloc(NPTS*sizeof(double));

    for (count=0;count<NPTS;count++){
        pp[count]=p[0]+dt*count;
    }

    // Use function.
    wiginterpd(p,q,npts,pp,qq,NPTS,0);

	double xp=-10,xq;
	wiginterpd(p,q,npts,&xp,&xq,1,0);
	printf("%.3lf\n",xq);

    // Output result.
    fp=fopen("data/wiginterpd_out_C","w");
    for (count=0;count<NPTS;count++){
        fprintf(fp,"%.4lf\t%.8e\n",pp[count],qq[count]);
    }
    fclose(fp);

    free(p);
    free(q);
    free(pp);
    free(qq);

    return 0;
}
// SAC Benchmark:
// See wiginterpd_matlab.m
