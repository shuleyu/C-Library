#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<ASU_tools.h>

int main(){

    int    NPTS_struct,NPTS_source,NPTS_signal,NPTS_decon,count,P1,P2;
    FILE   *fp;
    double delta,sigma,gwidth,*structure,*source,*signal,**decon,waterlevel,taperwidth,sigma_smooth,secondarrival,secondamp,ulvzarrival,ulvzamp;

    // Parameters.
    delta=0.025;
    sigma=2;
    gwidth=50;
    sigma_smooth=0.1;
    waterlevel=0.1;
    taperwidth=0.1;
    secondarrival=3;
    secondamp=0.3;
    ulvzarrival=10;
    ulvzamp=0.1;


    // Find length of traces.
    NPTS_struct=(int)((2+2*ulvzarrival)/delta);
    NPTS_source=1+2*(int)ceil(gwidth/2/delta);
    NPTS_signal=NPTS_struct+NPTS_source-1;
    NPTS_decon=(NPTS_signal>=NPTS_source)?(2*NPTS_signal):(2*NPTS_source);

    structure=(double *)malloc(NPTS_struct*sizeof(double));
    source=(double *)malloc(NPTS_source*sizeof(double));
    signal=(double *)malloc(NPTS_signal*sizeof(double));
    decon=(double **)malloc(sizeof(double *));
    decon[0]=(double *)malloc(NPTS_decon*sizeof(double));


    // Make Strucuture.
    for (count=0;count<NPTS_struct;count++){
        structure[count]=0;
    }
    structure[NPTS_struct/2]=1;
    structure[NPTS_struct/2-(int)(ulvzarrival/delta)]=-ulvzamp;
    structure[NPTS_struct/2+(int)(ulvzarrival/delta)]=ulvzamp;


    // Make source, use gaussian with sigma.
    source[NPTS_source/2]=gaussian(0,sigma,0);
    for (count=0;count<NPTS_source/2;count++){
        source[count]=gaussian(-(NPTS_source/2-count)*delta,sigma,0);
        source[NPTS_source-1-count]=source[count];
    }


    for (count=0;count<NPTS_source-(int)(secondarrival/delta);count++){
        source[count]+=secondamp*source[count+(int)(secondarrival/delta)];
    }
    reverse_array(source,NPTS_source);
//     shift_array(source,NPTS_source,(int)(3/delta));
    normalized(source,NPTS_source);
	max_vald(source,NPTS_source,&P1);


    // Make signal.
    convolve(structure,source,NPTS_struct,NPTS_source,signal);
    normalized(signal,NPTS_signal);
    taperd(signal,NPTS_signal,taperwidth);
	max_vald(signal,NPTS_signal,&P2);

    // Decon.
    waterlevel_decon(&signal,1,NPTS_signal,source,NPTS_source,P1,&P2,decon,waterlevel,delta,0,NULL,NULL,NULL,NULL,NULL,NULL);


    // Smooth and normalze.
    gaussblur_1d(decon,1,NPTS_decon,delta,sigma_smooth,gwidth,decon);
    normalized(decon[0],NPTS_decon);


    // Output.
    fp=fopen("data/waterlevel_decon_out_structure","w");
    for (count=0;count<NPTS_struct;count++){
        fprintf(fp,"%lf\t%lf\n",delta*count,structure[count]);
    }
    fclose(fp);

    fp=fopen("data/waterlevel_decon_out_source","w");
    for (count=0;count<NPTS_source;count++){
        fprintf(fp,"%lf\t%lf\n",delta*count,source[count]);
    }
    fclose(fp);

    fp=fopen("data/waterlevel_decon_out_signal","w");
    for (count=0;count<NPTS_signal;count++){
        fprintf(fp,"%lf\t%lf\n",delta*count,signal[count]);
    }
    fclose(fp);

    fp=fopen("data/waterlevel_decon_out_decon","w");
    for (count=0;count<2*NPTS_signal;count++){
        fprintf(fp,"%lf\t%lf\n",delta*count,decon[0][count]);
    }
    fclose(fp);

    free(structure);
    free(source);
    free(signal);
    free(decon[0]);
    free(decon);

    return 0;
}
// Visualize data.
// See waterlevel_decon_matlab.m
