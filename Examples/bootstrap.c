#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ASU_tools.h>

int main(){

    int    nptsx,nptsy,count,count2,BootNum;
    FILE   *fp,*fp2;
    double **p,*w,**Boot,*sigma,*avr;
    char   tmpstr[1000];

    BootNum=5000;
    nptsy=100;

    strcpy(tmpstr,"data/bootstrap_in");
    nptsx=filenr(tmpstr);
    w=(double *)malloc(nptsx*sizeof(double));

    // Malloc space.
    p=(double **)malloc(nptsx*sizeof(double *));
    for (count=0;count<nptsx;count++){
        p[count]=(double *)malloc(nptsy*sizeof(double));
    }

    Boot=(double **)malloc(BootNum*sizeof(double *));
    for (count=0;count<BootNum;count++){
        Boot[count]=(double *)malloc(nptsy*sizeof(double));
    }

    sigma=(double *)malloc(nptsy*sizeof(double));
    avr=(double *)malloc(nptsy*sizeof(double));

    // Read input.
    fp=fopen(tmpstr,"r");
    for (count=0;count<nptsx;count++){
        for (count2=0;count2<nptsy;count2++){
            fscanf(fp,"%lf",&p[count][count2]);
        }
        w[count]=p[count][0];
    }
    fclose(fp);


    // Use function.
    bootstrap(p,nptsx,nptsy,BootNum,avr,sigma,Boot,0,w);

    // Output.
    fp=fopen("data/bootstrap_out","w");
    for (count=0;count<nptsy;count++){
        for (count2=0;count2<BootNum;count2++){
            fprintf(fp,"%.6e\t",Boot[count2][count]);
        }
        fprintf(fp,"\n");
    }
    fclose(fp);

    fp2=fopen("data/bootstrap_out_avr_std","w");
    for (count=0;count<nptsy;count++){
        fprintf(fp2,"%.6e\t%.6e\n",avr[count],sigma[count]);
    }
    fclose(fp2);


    for (count=0;count<BootNum;count++){
        free(Boot[count]);
    }
    for (count=0;count<nptsx;count++){
        free(p[count]);
    }

    free(Boot);
    free(p);
    free(sigma);

    return 0;
}
