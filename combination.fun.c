// Done.

#include<stdio.h>
#include<stdlib.h>
#include<ASU_tools.h>

/**************************************************************
 * This C function returns the combination of input integers.
 *
 * int n  ----  Lower number.
 * int k  ----  Upper number.
 *
 * Return C_{n}^{k}
 *
 * Shule Yu
 * Mar 10 2015
 *
 * Key words: combination
**************************************************************/

double combination(int n, int k){
    
    if ( n < 0 || k < 0 || k > n ){
        printf("In %s: input error...\n",__func__);
        exit(1);
    }

    int    count;
    double ans;

    ans=1;
    for (count=1;count<k+1;count++){
        ans*=1.0*(n-k+count)/count;
    }

    return ans;
}
