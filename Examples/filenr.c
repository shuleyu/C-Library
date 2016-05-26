#include<stdio.h>
#include<string.h>
#include<ASU_tools.h>

int main(){

    char tmpstr[100];
    strcpy(tmpstr,"filenr.c");

    // Use function.
    printf("File %s has %d line.\n",tmpstr,filenr(tmpstr));

    return 0;
}
