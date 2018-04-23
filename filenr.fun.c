#include<stdio.h>
#include<stdlib.h>
#include<ASU_tools.h>

/************************************************************
 * This C function count how many lines within one ascii file.
 * Same as the bash command `wc -l < ${filename}` as long as
 * each line of the file doesn't exceed 10000 characters.
 *
 * double *p    ----  Array pointer.
 * int    npts  ----  Array npts.
 *
 * Shule Yu
 * Aug 28 2015
 *
 * Key words: File, line, number
************************************************************/

int filenr(const char *filename){

    int  count;
    char *tmpstr;
    FILE *fp;

    fp=fopen(filename,"r");

    if (fp==NULL){
        printf("In %s: File open Error ...\n",__func__);
        return -1;
    }

    count=0;
    tmpstr=(char *)malloc(10000*sizeof(char));

    fgets(tmpstr,10000,fp);

    while (!feof(fp)){
        count++;
        fgets(tmpstr,10000,fp);
    }

    free(tmpstr);
    fclose(fp);

    return count;
}
