#include<stdio.h>
#include<math.h>
#include<ASU_tools.h>

int main(){

    FILE   *fpout;
    double RE,Depth,dr;
    double rho,vpv,vph,vsv,vsh,qu,qk,yita;

    RE=6371.0;
    dr=0.5;

    fpout=fopen("data/prem_iso_out","w");
    fprintf(fpout,"<Depth>    <Vp>    <Vs>    <Rho>    <Qu>    <Qk>    <Yita>\n");
    Depth=0;
    while (Depth<=RE){
        prem(Depth,1,0,&rho,&vpv,&vph,&vsv,&vsh,&qu,&qk,&yita);
        fprintf(fpout,"%10.3lf\t%10.4lf\t%10.4lf\t%10.3lf\t%10.3lf\t%10.3lf\t%10.3lf\n",Depth,vpv,vsv,rho,qu,qk,yita);
        Depth+=dr;
    }
    fclose(fpout);

    fpout=fopen("data/prem_out","w");
    fprintf(fpout,"<Depth>    <vpv>    <vph>    <vsv>    <vsh>    <rho>    <Qu>    <Qk>    <Yita>\n");
    Depth=0;
    while (Depth<=RE){
        prem(Depth,0,0,&rho,&vpv,&vph,&vsv,&vsh,&qu,&qk,&yita);
        fprintf(fpout,"%10.3lf\t%10.4lf\t%10.4lf\t%10.3lf\t%10.3lf\t%10.3lf\t%10.3lf\t%10.3lf\t%10.3lf\n",Depth,vpv,vph,vsv,vsh,rho,qu,qk,yita);
        Depth+=dr;
    }
    fclose(fpout);

    fpout=fopen("data/prem_smoothed_out","w");
    fprintf(fpout,"<Depth>    <Vp>    <Vs>    <Rho>\n");
    Depth=0;
    while (Depth<=RE){
        prem_smoothed(Depth,&rho,&vpv,&vph,&vsv,&vsh,&qu,&qk,&yita,1,1,1,1);
        fprintf(fpout,"%10.3lf\t%10.4lf\t%10.4lf\t%10.3lf\n",Depth,vpv,vsv,rho);
        Depth+=dr;
    }
    fclose(fpout);

    return 0;
}
