#include<stdio.h>
#include<ASU_tools.h>

int main(){
    
    double a,b,c,d,e,f;
    a=1;
    b=2;
    c=1;
    d=0;
    
    // Use function:
    complex_divide(a,b,c,d,&e,&f);

    printf("%.10lf + %.10lf i\n",a,b);
    printf("------------------------------------------------ = \n");
    printf("%.10lf + %.10lf i\n\n",c,d);
    printf("%.10lf + %.10lf i\n\n",e,f);

    // Use function:
    complex_divide(a,b,c,d,&a,&b);

    printf("In place result:\n");
    printf("%.10lf + %.10lf i\n",a,b);
    
    return 0;    
}

// Matlab benchmark:
// a=1.332;
// b=23.42;
// c=23.75;
// d=9.35;
// (a+b*j)/(c+d*j)
