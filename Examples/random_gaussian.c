#include<stdio.h>
#include<stdlib.h>
#include<ASU_tools.h>

int main(){

    int    count,count2,npts,loop;
    double *p,mu,sigma;
    FILE   *fpout;

    loop=10;
    npts=300;
    mu=1;
    sigma=0.3;
    p=(double *)malloc(npts*sizeof(double));

    fpout=fopen("data/random_gaussian_out","w");

    for (count=0;count<loop;count++){

        // Use function.
        random_gaussian(p,npts,mu,sigma);

        // Output.
        for (count2=0;count2<npts-1;count2++){
            fprintf(fpout,"%.7lf\t",p[count2]);
        }
        fprintf(fpout,"%.7lf\n",p[count2]);
    }

    fclose(fpout);


//     int    Num;
//     double *randdouble,mu,sigma;
// 
//     Num=10000;
//     mu=1;
//     sigma=0.3;
// 
//     randdouble=(double *)malloc(Num*sizeof(double));
// 
//     random_gaussian(randdouble,Num,mu,sigma);
// 
//     printf("Mean: %lf\n",mean_d(randdouble,Num));
//     printf("Std: %lf\n",std_d(randdouble,Num));

    return 0;
}
