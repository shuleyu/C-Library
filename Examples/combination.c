#include<stdio.h>
#include<ASU_tools.h>

int main(){

    int n,k;

    n=10;
    k=7;

    // Use function.
    printf("C_%d^%d = %.5e\n",n,k,combination(n,k));

    return 0;    
}
