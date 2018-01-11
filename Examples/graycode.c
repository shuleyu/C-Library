#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<ASU_tools.h>

int main(){

    int   Bit,**Ans,Cnt,Cnt2,Break;

	Bit=5;
	Break=8;

	Ans=(int **)malloc(pow(2,Bit)*sizeof(int *));
	for (Cnt=0;Cnt<pow(2,Bit);Cnt++){
		Ans[Cnt]=(int *)malloc(Bit*sizeof(int));
	}

    // Use function.
	graycode(Bit,Ans);

	for (Cnt=0;Cnt<pow(2,Bit);Cnt++){
		for (Cnt2=0;Cnt2<Bit;Cnt2++){
			printf("%1d",Ans[Cnt][Cnt2]);
		}
		if (Cnt==pow(2,Bit)-1){
			printf("\n");
		}
		else{
			if (Cnt%Break==(Break-1)){
				printf(" -> \n");
			}
			else{
				printf(" -> ");
			}
		}
	}
	printf("\n");

    return 0;
}
