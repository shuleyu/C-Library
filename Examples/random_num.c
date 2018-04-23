#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<ASU_tools.h>

// Example program 1, output random numbers to file.
// int main(){
// 
//     int    count,count2,npts,loop;
//     double *p;
//     FILE   *fpout;
// 
//     loop=1;
//     npts=1000;
//     p=(double *)malloc(npts*sizeof(double));
// 
//     fpout=fopen("data/random_num_out","w");
// 
//     for (count=0;count<loop;count++){
// 
//         // Use function.
//         random_num(p,npts);
// 
//         // Output.
//         for (count2=0;count2<npts-1;count2++){
//             fprintf(fpout,"%.7lf\t",p[count2]);
//         }
//         fprintf(fpout,"%.7lf\n",p[count2]);
//     }
// 
//     fclose(fpout);
// 
//     return 0;
// }

// Example program 2. Calculate \pi.
int main(){
    
    int    npts,count,N;
    double *p;

    npts=10000000;
    p=(double *)malloc(2*npts*sizeof(double));
    random_num(p,2*npts);

    // Reset range to -1 to 1.
    for (count=0;count<2*npts;count++){
        p[count]=p[count]*2-1;
    }

    // Count points located within unit circle.
    N=0;
    for (count=0;count<npts;count++){
        if (pow(p[count],2)+pow(p[count+npts],2)<1){
            N++;
        }
    }

    printf("PI is: %.5lf\n",(1.0*N)/npts*4);
    
    return 0;
}
