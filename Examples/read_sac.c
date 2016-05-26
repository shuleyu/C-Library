#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>
#include<ASU_tools.h>

int main(){

    int    fileN,nptsy,count,count2,flag_filter,*bad;
    char   **filelist;
    FILE   *fpout;
    double *ptime,**data,C1,C2,taperwidth,delta,F1,F2;

    C1=-200;
    C2=50;
    taperwidth=0.02;
    delta=0.01;

    fileN=2;
    nptsy=1+(int)ceil((C2-C1)/delta);
    flag_filter=2;
    F1=0.02;
    F2=0.3;

    bad=(int *)malloc(fileN*sizeof(int));
    ptime=(double *)malloc(fileN*sizeof(double));

    data=(double **)malloc(fileN*sizeof(double *));
    for (count=0;count<fileN;count++){
        data[count]=(double *)malloc(nptsy*sizeof(double));
    }

    filelist=(char **)malloc(fileN*sizeof(char *));
    for (count=0;count<fileN;count++){
        filelist[count]=(char *)malloc(200*sizeof(char));
    }

    ptime[0]=1234.695;
    ptime[1]=1263.775;
    strcpy(filelist[0],"data/200608250044.CN.LMN.BHT.sac");
    strcpy(filelist[1],"data/200608250044.TA.X13A.BHT.sac");

    // Use Function.
    fileN=read_sac(data,fileN,nptsy,ptime,C1,delta,F1,F2,2,2,flag_filter,1,taperwidth,filelist,bad);
    
    // Output data.
    printf("Successfully read in %d traces.\n",fileN);

    fpout=fopen("data/read_sac_out_C","w");
    for (count=0;count<nptsy;count++){
        for (count2=0;count2<fileN;count2++){
            fprintf(fpout,"%.4lf\t%.6e\t",C1+ptime[count2]+count*delta,data[count2][count]);
        }
        fprintf(fpout,"\n");
    }
    fclose(fpout);

    for (count=0;count<fileN;count++){
        free(filelist[count]);
        free(data[count]);
    }
    free(filelist);
    free(data);
    free(ptime);
    
    return 0;
}
