#include<stdio.h>
#include<math.h>
#include<ASU_tools.h>

int main(){

    int    xnpts,ynpts,shift,count;
    FILE   *fpin,*fpout;
    double x[1200],y[14000];
    double dt,ccc;

    xnpts=1200;
    ynpts=14000;
    dt=0.025;

    fpin=fopen("data/cc_infile1","r");
    for (count=0;count<xnpts;count++){
        fscanf(fpin,"%lf",x+count);
    }
    fclose(fpin);

    fpin=fopen("data/cc_infile2","r");
    for (count=0;count<ynpts;count++){
        fscanf(fpin,"%lf",y+count);
    }
    fclose(fpin);

    // Use function.
    CC(x,xnpts,y,ynpts,&shift,&ccc);
    printf("Shift: %d\nShift_time: %.2lf\nCCC: %.3lf\n",shift,shift*dt,ccc);

    fpout=fopen("data/cc_out","w");
    fprintf(fpout,"%d\n",shift);
    fclose(fpout);

    return 0;
}
// matlab equivalent:
// see cc_matlab.m
