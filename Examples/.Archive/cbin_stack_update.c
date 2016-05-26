#include<stdio.h>
#include<stdlib.h>
#include<ASU_tools.h>

int main(int argc, char **argv){

    int    count,count2,**index,npts,N,M;
    double **data,*plon,*plat,*weight,*blon,*blat,*radius,**stack, **std;

    npts=1;
    N=10;
    M=2;

    plon=(double *)malloc(N*sizeof(double));
    plat=(double *)malloc(N*sizeof(double));
    weight=(double *)malloc(N*sizeof(double));
    blon=(double *)malloc(M*sizeof(double));
    blat=(double *)malloc(M*sizeof(double));
    radius=(double *)malloc(M*sizeof(double));
    data=(double **)malloc(N*sizeof(double *));
    index=(int **)malloc(N*sizeof(int *));
    stack=(double **)malloc(M*sizeof(double *));
    std=(double **)malloc(M*sizeof(double *));

    for (count=0;count<N;count++){
        data[count]=(double *)malloc(npts*sizeof(double));
        index[count]=(int *)malloc(M*sizeof(int));
    }
    for (count=0;count<M;count++){
        stack[count]=(double *)malloc(npts*sizeof(double));
        std[count]=(double *)malloc(npts*sizeof(double));
    }

    random_num(plon,N);
    random_num(plat,N);

    random_num(blon,M);
    random_num(blat,M);

    radius[0]=0.5;
    radius[1]=0.2;

    for (count=0;count<N;count++){
        weight[count]=1;
        data[count][0]=count;
    }

    printf("Bins_before: { Lon, Lat, Radius }:\n");
    for (count=0;count<M;count++){
        printf("{ %.2lf, %.2lf, %.2lf }\n",blon[count],blat[count],radius[count]);
    }
    printf("\n");

    cbin_stack_update(data,plon, plat, 0, weight, N, npts, blon, blat, radius, M, index, stack, std, 1, 0.5);

    printf("Points: { Lon, Lat } { Dist1, Dist2 } {Value, Weight}\n");
    for (count=0;count<N;count++){
        printf("{ %.2lf, %.2lf } { %.2lf, %.2lf } { %.2lf, %.2lf }\n",plon[count],plat[count],gcpdistance(plon[count],plat[count],blon[0],blat[0]),gcpdistance(plon[count],plat[count],blon[1],blat[1]),data[count][0], weight[count]);
    }
    printf("\n");

    printf("Bins: { Lon, Lat, Radius }:\n");
    for (count=0;count<M;count++){
        printf("{ %.2lf, %.2lf, %.2lf }\n",blon[count],blat[count],radius[count]);
    }
    printf("\n");

    printf("Points: { Index1 , Index2 }:\n");
    for (count2=0;count2<N;count2++){
        printf("{ ");
        for (count=0;count<M;count++){
            printf("%d, ",index[count2][count]);
        }
        printf("}\n");
    }
    printf("\n");

    printf("Points: { Stack, Std } :\n");
    for (count=0;count<M;count++){
        printf("{ %lf, %lf }\n",stack[count][0], std[count][0]);
    }
    printf("\n");

    free(plon);
    free(plat);
    free(weight);
    free(blon);
    free(blat);
    free(radius);

    for (count=0;count<N;count++){
        free(data[count]);
        free(index[count]);
    }
    for (count=0;count<M;count++){
        free(stack[count]);
        free(std[count]);
    }
    free(data);
    free(index);
    free(stack);
    free(std);

    return 0;
}
