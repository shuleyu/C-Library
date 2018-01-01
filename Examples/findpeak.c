#include<stdio.h>
#include<stdlib.h>
#include<ASU_tools.h>

int main(){

    int   npts=100,Peak=50,count;
	double p[100];

	random_num(p,npts);

    // Use function.
    printf("Widow: %d ~ %d\n",Peak-10,Peak+10);
	findpeak(p,100,&Peak,-10,20);
    printf("Peak is at: %d\n",Peak);

	for (count=35;count<65;count++){
		printf("%d\t%.4lf\n",count,p[count]);
	}

    return 0;
}
