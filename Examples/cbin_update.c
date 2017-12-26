#include<stdio.h>
#include<stdlib.h>
#include<ASU_tools.h>

int main(){

	// Make bins.
	double BinInc=5;
	int    Nb=meshsize(-20,20,BinInc,0);
	double *blon=(double *)malloc(Nb*sizeof(double));
	double *blat=(double *)malloc(Nb*sizeof(double));
	double *radius=(double *)malloc(Nb*sizeof(double));
	meshthem(blat,Nb,-20,20,BinInc,0);
	for (int i=0;i<Nb;++i){
		blon[i]=0;
		radius[i]=2;
	}
	

	// Make points.
	double PIncx=0.5,PIncy=0.5;
	int Npx=meshsize(-10,10,PIncx,0);
	int Npy=meshsize(-25,25,PIncy,0);
	double *plon=(double *)malloc(Npx*Npy*sizeof(double));
	double *plat=(double *)malloc(Npx*Npy*sizeof(double));
	for (int i=0;i<Npy;++i){
		for (int j=0;j<Npx;++j){
			plon[i*Npx+j]=-10+PIncx*j;
			plat[i*Npx+j]=-25+PIncy*i;
		}
	}

	// Make results.
	int **index=(int **)malloc(Npx*Npy*sizeof(int *));
	for (int i=0;i<Npx*Npy;++i)
		index[i]=(int *)malloc(Nb*sizeof(int));

	// Use function.
	cbin_update(plon,plat,Npx*Npy,blon,blat,radius,Nb,index);

	// Output.
    FILE *fpout;
	int flag=1;

    fpout=fopen("data/cbin_update_index","w");
	for (int i=0;i<Npy;++i){
		for (int j=0;j<Npx;++j){
			flag=1;
			for (int k=0;k<Nb;++k){
				if (index[(Npy-1-i)*Npx+j][k]==1){
					fprintf(fpout,"%-3d",k+1);
					flag=0;
					break;
				}
			}
			if (flag==1) fprintf(fpout,"0  ");
		}
		fprintf(fpout,"\n");
	}
	fclose(fpout);

    fpout=fopen("data/cbin_update_bincenter","w");
	for (int i=0;i<Nb;++i)
		fprintf(fpout,"%.3lf %.3lf\n",blon[i],blat[i]);
	fclose(fpout);

    return 0;
}
