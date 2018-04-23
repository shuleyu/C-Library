#include<stdio.h>
#include<ASU_tools.h>

int main(){

    int i;
    double x[20];

    // Use function.
//     trifun(x,20,0.2);
    trifun(x,20,2.0);

    for (i=0;i<20;i++){
        printf("%.3lf\t",x[i]);
    }
    printf("\n");

    return 0;
}
