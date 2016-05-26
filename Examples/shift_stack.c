#include<stdio.h>
#include<stdlib.h>
#include<ASU_tools.h>

int main(){
    int    count,count2,*shift;
    double **a,*weight,b[5],c[5];

    a=(double **)malloc(3*sizeof(double *));
    for (count=0;count<3;count++){
        a[count]=(double *)malloc(5*sizeof(double));
    }
    shift=(int *)malloc(3*sizeof(int));
    weight=(double *)malloc(3*sizeof(double));

    for (count=0;count<3;count++){
        for (count2=0;count2<5;count2++){
            a[count][count2]=(1+count)*(1+count2);
        }
    }

    shift[0]=1;
    shift[1]=-1;
    shift[2]=2;

    weight[0]=0.1;
    weight[1]=1.0;
    weight[2]=0.9;

    // Use function.
    shift_stack(a,3,5,1,shift,1,weight,b,c);

    // Print Output.
    printf("Origin Array:\n");
    for (count=0;count<3;count++){
        for (count2=0;count2<5;count2++){
            printf("%lf\t",a[count][count2]);
        }
        printf("(%d) (%lf)\n",shift[count],weight[count]);
    }

    printf("\nStack:\n");
    for (count=0;count<5;count++){
        printf("%lf\t",b[count]);
    }
    printf("\n");

    printf("\nStandard Deviation:\n");
    for (count=0;count<5;count++){
        printf("%lf\t",c[count]);
    }
    printf("\n");
    return 0;
}
