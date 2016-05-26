#include<stdio.h>
#include<stdlib.h>
#include<ASU_tools.h>

int main(){

    int    count,npts1,npts2;
    FILE   *fpin1,*fpin2;
    double x,y;

    npts1=filenr("data/findjunction.infile1");
    npts2=filenr("data/findjunction.infile2");
    double *x1=(double *)malloc(npts1*sizeof(double));
    double *y1=(double *)malloc(npts1*sizeof(double));
    double *x2=(double *)malloc(npts2*sizeof(double));
    double *y2=(double *)malloc(npts2*sizeof(double));

    fpin1=fopen("data/findjunction.infile1","r");
    for (count=0;count<npts1;count++){
        fscanf(fpin1,"%lf%lf",&y1[count],&x1[count]);
    }
    fclose(fpin1);


    fpin2=fopen("data/findjunction.infile2","r");
    for (count=0;count<npts2;count++){
        fscanf(fpin2,"%lf%lf",&y2[count],&x2[count]);
    }
    fclose(fpin2);

    // Use function.

    if (findjunction(x1,y1,npts1,x2,y2,npts2,1e-5,&x,&y)==1){
        printf("No junction points... \n");
    }
    else{
        printf("%.8lf\t%.8lf\n",x,y);
    }

	free(x1);
	free(y1);
	free(x2);
	free(y2);

    return 0;
}
