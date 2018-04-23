#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>
#include<sac.h>
#include<sacio.h>
#include<ASU_tools.h>

#define DMAXL 2000000

// 2 functions
// read_sac
// read_sac_fixdel

/*******************************************************************************************
 * This C function use sac libaries to load data into RAM for
 * further use.
 *
 * double **data        ----  An 2D array to store read in data.
 * int    nptsx         ----  X dimension of data. ( trace number )
 * int    nptsy         ----  Y dimension of data. ( trace NPTS, need to be pre-calculated )
 *
 * (for read_sac_fixdel:)
 * int    *nptsy        ----  Adjusted data length to the cut time period and original 
 *                               sampling rate.
 *
 * double *CutAround    ----  Cut around this time value. e.g. a phase arrival ( sec. )
 * double Cut           ----  Begin time in result relative to CutAround. ( sec. )
 *                            Cut < 0 means cut before CutAround.
 *                            If Cut window is not covered by data length, notify as bad.
 * double delta         ----  Interpolate / Decimate to this sampling rate. ( sec. )
 *                            Data length (in sec.) is (nptsy-1)*delta.
 * (for read_sac_fixdel:)
 * double *delta        ----  This fixdel is a little strange. It require all SAC file has
 *                               the same sampling rate (usually this is used on synthetics).
 *                               The only difference from read_sac is that no interpolation
 *                               happens in this one. Input delta should approximate the one
 *                               in SAC files to ensure the data length read in is correct,
 *                               the output value will be changed to the real SAC sampling rate.
 *
 * double f1            ----  Filter left corner freq 1.
 *                            Ignored when flag_filter == 1
 * double f2            ----  Filter right corner freq 2.
 *                            Ignored when flag_filter == 3
 * int    order         ----  Filter order.
 * int    passes        ----  Pass.
 * int    flag_filter   ----  Type of filter applied to data.
 *                            0 -- No filter.
 *                            1 -- Butterworth low pass.
 *                            2 -- Butterworth band pass.
 *                            3 -- Butterworth high pass.
 * int    flag_retrend  ----  After the cut, whether apply a retrend operation.
 *                               0 -- No retrend after cut.
 *                               1 -- Retrend after cut.
 * double taperwidth    ----  After the cut, apply a taper before filter.
 * char   **filelist    ----  Sac file list ( use absolute dir with file basename )
 * int    *bad          ----  Indicate this data has error.
 *
 * Shule Yu
 * Oct 01 2014
 *
 * Key words: sac, IO, read data.
*******************************************************************************************/

int read_sac(double **data,int nptsx,int nptsy,double *CutAround,double Cut,double delta,double f1,double f2,int order, int passes,int flag_filter, int flag_retrend, double taperwidth,char **filelist,int *bad){

    int    nerr,maxl,count,count2,fileN,rawnpts,win_rawbegin,win_rawnpts,interp_flag;
    float  *rawtime,*rawdata,rawbeg,rawdel;
    double *newtime,CutTime,dlength;

    maxl=DMAXL;
    dlength=(nptsy-1)*delta;

    // Malloc auxilliary space.
    rawtime=(float *)malloc(DMAXL*sizeof(float));
    rawdata=(float *)malloc(DMAXL*sizeof(float));
    newtime=(double *)malloc(nptsy*sizeof(double));

    // Read in sac files.
    fileN=0;
    for (count=0;count<nptsx;count++){

        CutTime=Cut+CutAround[count];
        for (count2=0;count2<nptsy;count2++){
            newtime[count2]=CutTime+delta*count2;
        }

        // Load sac file.
        // Evenly sampling, use rsac1.
        rsac1(filelist[count],rawdata,&rawnpts,&rawbeg,&rawdel,&maxl,&nerr,strlen(filelist[count]));

        if (nerr>0){ // uneven sampling, use rsac2.
            interp_flag=1;
            rsac2(filelist[count],rawdata,&rawnpts,rawtime,&maxl,&nerr,strlen(filelist[count]));
        }
        else{
            interp_flag=0;
            for (count2=0;count2<rawnpts;count2++){
                rawtime[count2]=rawbeg+count2*rawdel;
            }
        }

        // Test if it's a bad record.
        if (nerr>0){
            printf("In %s: SAC read error for file %s ...\n",__func__,filelist[count]);
            bad[count]=1;
            continue;
        }

        // Check the coverage of cut window.
        if ( CutTime<rawtime[0] || rawtime[rawnpts-1]<CutTime+dlength ){
            printf("In %s: Cut window not suitable for file %s ...\n",__func__,filelist[count]);
            bad[count]=1;
            continue;
        }

        // Check amplitude within the cut window, to see if it's a bad record.
        win_rawnpts=0;
        win_rawbegin=0;
        for (count2=0;count2<rawnpts;count2++){
            if (rawtime[count2] <= CutTime){
                win_rawbegin=count2;
            }
            if ( CutTime <= rawtime[count2] && rawtime[count2] <= CutTime+dlength ){
                win_rawnpts++;
            }
        }

        if ( amplitude(rawdata+win_rawbegin,win_rawnpts) < 1e-20 ){
            printf("In %s: Small amplitude file %s ... \n",__func__,filelist[count]);
            bad[count]=1;
            continue;
        }

        // Interpolate / Decimate then cut data.
        wiginterp_f(rawtime,rawdata,rawnpts,newtime,data[count],nptsy,interp_flag);
//         if (delta>rawdel+0.00001){
//             printf("In %s: Aliasing warning: %s, %.2e Hz -> %.2e Hz \n",__func__,filelist[count],rawdel,delta);
//         }


        // Retrend.
        if (flag_retrend!=0){
            retrendd(CutTime,data[count],nptsy,delta);
        }

        // Taper
        taperd(data[count],nptsy,taperwidth);

        // Filter.
        if (flag_filter==1){
            butterworth_lp(&data[count],1,nptsy,delta,order,passes,f2,&data[count]);
        }
        if (flag_filter==2){
            butterworth_bp(&data[count],1,nptsy,delta,order,passes,f1,f2,&data[count]);
        }
        if (flag_filter==3){
            butterworth_hp(&data[count],1,nptsy,delta,order,passes,f1,&data[count]);
        }

        bad[count]=0;
        fileN++;

    } // End of reading from filelist.

    free(rawtime);
    free(rawdata);
    free(newtime);

    return fileN;
}

int read_sac_fixdel(double **data,int nptsx,int *nptsy,double *CutAround,double Cut,double *delta,double f1,double f2,int order, int passes,int flag_filter, int flag_retrend, double taperwidth,char **filelist,int *bad){

    int    nerr,maxl,count,count2,fileN,rawnpts,win_rawbegin,win_rawnpts,del_flag;
    float  *rawdata,rawbeg,rawdel;
    double CutTime,dlength,del_double;

    maxl=DMAXL;
    del_flag=0;
    dlength=((*nptsy)-1)*(*delta);

    // Malloc auxilliary space.
    rawdata=(float *)malloc(DMAXL*sizeof(float));

    // Read in sac files.
    fileN=0;
    for (count=0;count<nptsx;count++){

        CutTime=Cut+CutAround[count];

        // Load sac file.
        // Evenly sampling, use rsac1.
        rsac1(filelist[count],rawdata,&rawnpts,&rawbeg,&rawdel,&maxl,&nerr,strlen(filelist[count]));


        // Test if it's a bad record or unevenly sampled.
        if (nerr>0){
            printf("In %s: SAC read error for file %s ...\n",__func__,filelist[count]);
            bad[count]=1;
            continue;
        }


        // Check whether the data can be successfully load into the malloced space.
        if (rawdel < (*delta)) {
            printf("In %s: File %s has higher sampling rate than target...\n",__func__,filelist[count]);
            bad[count]=1;
            continue;
        }


        // Check whether the sampling rate of different traces various too much.
        if ((*delta)-rawdel>0.001){
            printf("In %s: File %s has a big difference in sampling rate with target...\n",__func__,filelist[count]);
            bad[count]=1;
            continue;
        }


        // Check the coverage of cut window.
        if ( CutTime<rawbeg || rawbeg+(rawnpts-1)*rawdel<CutTime+dlength ){
            printf("In %s: Cut window not suitable for file %s ...\n",__func__,filelist[count]);
            bad[count]=1;
            continue;
        }

        // Check amplitude within the cut window, to see if it's a bad record.
        win_rawbegin=(int)ceil((CutTime-rawbeg)/rawdel);
        win_rawnpts=(int)ceil(dlength/rawdel);

        if ( amplitude(rawdata+win_rawbegin,win_rawnpts) < 1e-20 ){
            printf("In %s: Small amplitude file %s ... \n",__func__,filelist[count]);
            bad[count]=1;
            continue;
        }


        // Check conformity of sampling rate.
        if (del_flag==0){ // If we haven't decide the new sampling rate.
            del_double=rawdel;
            (*nptsy)=1+(int)ceil(dlength/del_double);
            del_flag=1;
        }
        else { // If we have decided the new sampling rate, constrain the readin sampling rate.
            if (fabs(del_double-rawdel)>0.0005){
                printf("In %s: file %s has different sampling rate from previous file(s)... \n",__func__,filelist[count]);
                bad[count]=1;
                continue;
            }
        }


        // Cut data.
        for (count2=0;count2<(*nptsy);count2++){
            data[count][count2]=rawdata[win_rawbegin+count2];
        }

        // Retrend.
        if (flag_retrend!=0){
            retrendd(CutTime,data[count],(*nptsy),del_double);
        }

        // Filter.
        if (flag_filter!=0){
            taperd(data[count],(*nptsy),taperwidth);
        }
        if (flag_filter==1){
            butterworth_lp(&data[count],1,(*nptsy),del_double,order,passes,f2,&data[count]);
        }
        if (flag_filter==2){
            butterworth_bp(&data[count],1,(*nptsy),del_double,order,passes,f1,f2,&data[count]);
        }
        if (flag_filter==3){
            butterworth_hp(&data[count],1,(*nptsy),del_double,order,passes,f1,&data[count]);
        }

        bad[count]=0;
        fileN++;

    } // End of reading from filelist.
    (*delta)=del_double;

    free(rawdata);

    return fileN;
}
