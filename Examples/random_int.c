#include<stdio.h>
#include<stdlib.h>
#include<ASU_tools.h>

int main(){

    int  count,count2,min,max,npts,*p,loop;
    FILE *fpout;

    loop=1;
    min=1;
    max=1;
    npts=1000;

    p=(int *)malloc(npts*sizeof(int));

    fpout=fopen("data/random_int_out","w");
    for (count=0;count<loop;count++){

        // Use function.
        random_int(min,max,p,npts);

        // Output.
        for (count2=0;count2<npts;count2++){
            fprintf(fpout,"%d\t",p[count2]);
        }   
        fprintf(fpout,"\n");
    }   

    fclose(fpout);
    free(p);

    return 0;
}


// int main(){
// 
//     int  count,count2,*p,loop,*NPTS,key,N;
//     FILE *fpout;
// 
//     loop=10000;
//     NPTS=(int *)malloc(loop*sizeof(int));
//     fpout=fopen("data/random_coupon_out","w");
// 
//     for (N=1;N<1001;N++){
// 
//         p=(int *)malloc(loop*N*sizeof(int));
//         // Use function.
//         random_int(1,N,p,N*loop);
// 
//         for (count=0;count<loop;count++){
// 
// 
//             sort_quick_i(p+count*N,N);
// 
//             // Output.
//             key=p[count*N];
//             NPTS[count]=1;
//             for (count2=1+count*N;count2<N*(count+1);count2++){
//                 if (p[count2]!=key){
//                     key=p[count2];
//                     NPTS[count]++;
//                 }
//             }
//         }
// 
//         free(p);
// 
//         printf("N= %d    Distinct#= %lf    STD= %lf\n",N,mean_i(NPTS,loop),std_i(NPTS,loop));
// //         fprintf(fpout,"N= %d    Distinct#= %lf    STD= %lf\n",N,mean_i(NPTS,loop),std_i(NPTS,loop));
//     }
// 
//     free(NPTS);
//     fclose(fpout);
// 
//     return 0;
// }
