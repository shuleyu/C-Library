#include<stdio.h>
#include<ASU_tools.h>

int main(){
    int    pp,polarity;
    double a[5];
    a[0]=1;
    a[1]=7;
    a[2]=1;
    a[3]=-8;
    a[4]=1;

    // Use function.
    polarity=max_ampd(a,5,&pp);

    printf("Polarity: %d\nPosition: %d\nValue   : %.5lf\n",polarity,pp,a[pp]);

    return 0;
}
