#include<stdio.h>
#include<ASU_tools.h>

int main(){
    
    int    count,shift;
    double a[8];
    
    for (shift=-9;shift<=9;shift++){
        for (count=0;count<8;count++){
            a[count]=count*count;
        }

        printf("Shift        : %d\n",shift);

        printf("Origin Array : ");
        for (count=0;count<8;count++){
            printf("%.2lf\t",a[count]);
        }

        // Use function.
        shift_array(a,8,shift);

        printf("\nShifted Array: ");
        for (count=0;count<8;count++){
            printf("%.2lf\t",a[count]);
        }
        printf("\n\n");
    }
    
    
    return 0;
}
