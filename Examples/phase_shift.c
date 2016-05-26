#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<ASU_tools.h>

int main(){
    int    NPTS,count;
    FILE   *fp;
    double delta,sigma,gwidth,*gauss,*hilbert,shift;

    shift=-90;
    delta=0.025;
    sigma=2;
    gwidth=50;
    NPTS=2*(int)ceil(gwidth/2/delta);

    gauss=(double *)malloc(NPTS*sizeof(double));
    hilbert=(double *)malloc(NPTS*sizeof(double));

    // Make signal.
    for (count=0;count<NPTS/2;count++){
        gauss[count]=gaussian(-(NPTS/2-0.5-count)*delta,sigma,0);
        gauss[NPTS-1-count]=gauss[count];
    }
    normalized(gauss,NPTS);

    // Use function.
    phase_shift(gauss,NPTS,shift,hilbert);

    // Output.
    fp=fopen("data/phase_shift_in","w");
    for (count=0;count<NPTS;count++){
        fprintf(fp,"%lf\t%lf\n",count*delta,gauss[count]);
    }
    fclose(fp);

    fp=fopen("data/phase_shift_out","w");
    for (count=0;count<NPTS;count++){
        fprintf(fp,"%lf\t%lf\n",count*delta,hilbert[count]);
    }
    fclose(fp);

    // free space.
    free(gauss);
    free(hilbert);

    return 0;
}
// Visualize data.
// See phase_shift_matlab.m
