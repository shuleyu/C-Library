#include<stdio.h>
#include<ASU_tools.h>

int main(){

	int i;
    double x[11];

    // Use function.
    trifun(x,11,0);

	for (i=0;i<11;i++){
		printf("%.3lf\t",x[i]);
	}
	printf("\n");

    return 0;
}
