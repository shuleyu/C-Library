#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ASU_tools.h>

int main(){

    int    nptsx,nptsy,count,count2,BootNum;
    FILE   *fp,*fp2;
    double **p,*w,**Boot,*sigma;
    char   tmpstr[1000];

    BootNum=5000;
    nptsy=100;
	w=NULL;

    strcpy(tmpstr,"data/bootstrap_in");
    nptsx=filenr(tmpstr);

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

    // Read input.
    fp=fopen(tmpstr,"r");
    for (count=0;count<nptsx;count++){
        for (count2=0;count2<nptsy;count2++){
            fscanf(fp,"%lf",&p[count][count2]);
        }
    }
    fclose(fp);

    // Output.
    fp=fopen("data/bootstrap_out","w");
    fp2=fopen("data/bootstrap_out_std","w");

    // Use function.
    bootstrap(p,nptsx,nptsy,0,w,BootNum,Boot,sigma);

    for (count=0;count<BootNum;count++){
        for (count2=0;count2<nptsy-1;count2++){
            fprintf(fp,"%.6e\t",Boot[count][count2]);
        }
        fprintf(fp,"%.6e\n",Boot[count][count2]);
    }

    for (count=0;count<nptsy-1;count++){
        fprintf(fp2,"%.6e\t",sigma[count]);
    }
    fprintf(fp2,"%.6e\n",sigma[count]);

    fclose(fp);
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
