#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<ASU_tools.h>

/***********************************************************
 * This C function returns gray code for given bit number.
 *
 * int n      ----  Bit number.
 * int **ans  ----  Answer ( dimension: 2^n * n )
 *
 * Shule Yu
 * Dec 01 2015
 *
 * Key words: gray code.
***********************************************************/

void graycode(int n, int **ans){

	int **ans1,Cnt,Cnt2;

    if (n<=0){
        printf("In %s: Bit too small ...\n",__func__);
        return;
    }

	if (n==1){
		ans[0][0]=0;
		ans[1][0]=1;
	}
	else {
		ans1=(int **)malloc(pow(2,n-1)*sizeof(int *));
		for (Cnt=0;Cnt<pow(2,n-1);Cnt++){
			ans1[Cnt]=malloc((n-1)*sizeof(int));
		}
		graycode(n-1,ans1);

		for (Cnt=0;Cnt<pow(2,n-1);Cnt++){
			ans[Cnt][0]=0;
			ans[Cnt+(int)pow(2,n-1)][0]=1;
			for (Cnt2=0;Cnt2<n-1;Cnt2++){
				ans[Cnt][Cnt2+1]=ans1[Cnt][Cnt2];
				ans[Cnt+(int)pow(2,n-1)][Cnt2+1]=ans1[(int)pow(2,n-1)-Cnt-1][Cnt2];
			}
		}
		free(ans1);
	}

    return;
}
