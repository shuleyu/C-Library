#include<stdio.h>
#include<math.h>
#include<ASU_tools.h>

// 6 functions:
// CC
// CC_positive
// CC_trace
// CC_static
// CC_static_energy
// CC_limitshift

/**************************************************************************
 * This C function(s) calculate cross-correlation between x and y.
 *
 * Negative "shift" indicate y should move foreward.
 * Positive "shift" indicate y should move backward.
 * At "shift" we have the maximum value of |CCC|.
 * If there exists multiple "shift" for same |CCC|,
 * return the first found shift value.
 *
 * Cross-Correlation Coefficient (CCC) is defined as:
 *
 *           sum of x*y of the overlapping part
 *    CCC = -------------------------------------
 *            sqrt( (sum of x^2)*(sum of y^2) )
 *
 * Note: We remove the average of input signal before any calculation.
 *
 * (for CC_positive:)
 * Use CCC to replace |CCC|. (No flipping.)
 *
 * (for CC_trace:)
 * Also return the ccc trace in *result.
 * Which has length (xlen+ylen-1).
 * result start at array y ahead of x, therefore:
 * result[ylen-1+shift]=CCC*energy.
 *
 * (for CC_static:)
 * Shift=0 is fixed. Calculate the CCC value at shift=0.
 * therefore no "*shift" argument.
 *
 * (for CC_static_energy:)
 * Same as CC_static, with CCC defined as:
 *
 *           sum of x*y of the overlapping part * sqrt ( min( xx, yy ) )
 *    CCC = ---------------------------------------------------------------
 *            sqrt( (sum of x^2)*(sum of y^2) ) * sqrt ( max (xx, yy ) )
 *
 *         xx = sum of x^2
 *         yy = sum of y^2
 *
 * This design is for comparisons which need to take absolute
 * amplitude of the two trace into account.
 *
 * (for CC_limitshift:)
 * Find max|CCC| within |(*shift)*delta| < TimeLimit Shift window.
 *
 *
 * double *x      ----  Array pointer for signal x.
 * int    xlen    ----  Length of signal x.
 * double *y      ----  Array pointer for signal y.
 * int    ylen    ----  Length of signal y.
 * int    *shift  ----  Shift for y.
 * double *CCC    ----  CCC.
 *
 * (for CC_positive:)
 * int    polarity  ----  1: Don't flip x or y. Find max(CCC).
 *                       -1: Flip y, then find max(CCC).
 *
 * (for CC_trace:)
 * double *result  ----  CC trace. Unbiased.  1*(xlen+ylen-1).
 *
 * (for CC_static:)
 * No "*shift" argument.
 *
 * (for CC_static_energy:)
 * No "*shift" argument.
 *
 * (for CC_limitshift:)
 * double TimeLimit  ----  Shift time limit (in sec.)
 * double delta      ----  Sampling rate (in sec.)
 *
 * Shule Yu
 * Feb 05 2014
 *
 * Key words: cross-correlation.
**************************************************************************/

int CC(double *x, int xlen, double *y, int ylen, int *shift, double *CCC){

    int    count,tau,xBegin,xEnd;
    double energy,xx,yy,R;

    // Default error value;
    *shift=xlen+ylen-1;
    *CCC=0;

    // If signals are too short, return an error flag.
    if (xlen<=1){
        printf("In %s: X Sequence too short !\n",__func__);
        return 1;
    }
    if (ylen<=1){
        printf("In %s: Y Sequence too short !\n",__func__);
        return 1;
    }

    // Calculate x average and y average.
    double avrx=0,avry=0;
    for (count=0;count<xlen;count++){
        avrx+=x[count];
    }
    avrx/=xlen;
    for (count=0;count<ylen;count++){
        avry+=y[count];
    }
    avry/=ylen;

    // Denominator.
    xx=0;
    yy=0;
    for (count=0;count<xlen;count++){
        xx+=pow(x[count]-avrx,2);
    }
    for (count=0;count<ylen;count++){
        yy+=pow(y[count]-avry,2);
    }
    if ( sqrt(xx)< 1e-30 || sqrt(yy)< 1e-30 ){
        printf("In %s: Energy is zero !\n",__func__);
        return 2;
    }
    energy=sqrt(xx*yy);

    // Shifting and evaluating CCC at every shift value (tau).

    for (tau=-ylen+1;tau<xlen;tau++){
        xBegin=tau>0?tau:0;
        xEnd=xlen<(ylen+tau)?xlen:(ylen+tau);

        R=0;
        for (count=xBegin;count<xEnd;count++){
            R+=(x[count]-avrx)*(y[count-tau]-avry);
        }
        if ( fabs(*CCC)<fabs(R) ){
            *CCC=R;
            *shift=tau;
        }
    }

    *CCC/=energy;

    return 0;
}

int CC_positive(double *x, int xlen, double *y, int ylen, int *shift, double *CCC,int polarity){

    int    count,tau,xBegin,xEnd;
    double energy,xx,yy,R;

    // Default error value;
    *shift=xlen+ylen-1;
    *CCC=0;

    // If signals are too short, return an error flag.
    if (xlen<=1 || ylen<=1){
        printf("In %s: Sequence too short !\n",__func__);
        return 1;
    }

    // Calculate x average and y average.
    double avrx=0,avry=0;
    for (count=0;count<xlen;count++){
        avrx+=x[count];
    }
    avrx/=xlen;
    for (count=0;count<ylen;count++){
        avry+=y[count];
    }
    avry/=ylen;

    // Denominator.
    xx=0;
    yy=0;
    for (count=0;count<xlen;count++){
        xx+=pow(x[count]-avrx,2);
    }
    for (count=0;count<ylen;count++){
        yy+=pow(y[count]-avry,2);
    }
    if ( sqrt(xx)< 1e-30 || sqrt(yy)< 1e-30 ){
        printf("In %s: Energy is zero !\n",__func__);
        return 2;
    }
    energy=sqrt(xx*yy);

    // Shifting and evaluating CCC at every shift value (tau).

    for (tau=-ylen+1;tau<xlen;tau++){
        xBegin=tau>0?tau:0;
        xEnd=xlen<(ylen+tau)?xlen:(ylen+tau);

        R=0;
        for (count=xBegin;count<xEnd;count++){
            R+=(x[count]-avrx)*(y[count-tau]-avry)*polarity;
        }
        if ( *CCC<R ){
            *CCC=R;
            *shift=tau;
        }
    }

    *CCC/=energy;

    return 0;
}

int CC_trace(double *x, int xlen, double *y, int ylen, int *shift, double *CCC, double *result){

    int    count,tau,xBegin,xEnd;
    double energy,xx,yy;

    // Default error value;
    *shift=xlen+ylen-1;
    *CCC=0;

    // If signals are too short, return an error flag.
    if (xlen<=1 || ylen<=1){
        printf("In %s: Sequence too short !\n",__func__);
        return 1;
    }

    // Calculate x average and y average.
    double avrx=0,avry=0;
    for (count=0;count<xlen;count++){
        avrx+=x[count];
    }
    avrx/=xlen;
    for (count=0;count<ylen;count++){
        avry+=y[count];
    }
    avry/=ylen;

    // Denominator.
    xx=0;
    yy=0;
    for (count=0;count<xlen;count++){
        xx+=pow(x[count]-avrx,2);
    }
    for (count=0;count<ylen;count++){
        yy+=pow(y[count]-avry,2);
    }
    if ( sqrt(xx)< 1e-30 || sqrt(yy)< 1e-30 ){
        printf("In %s: Energy is zero !\n",__func__);
        return 2;
    }
    energy=sqrt(xx*yy);

    // Shifting and evaluating CCC at every shift value (tau).

    for (tau=-ylen+1;tau<xlen;tau++){
        xBegin=tau>0?tau:0;
        xEnd=xlen<(ylen+tau)?xlen:(ylen+tau);

        result[ylen-1+tau]=0;
        for (count=xBegin;count<xEnd;count++){
            result[ylen-1+tau]+=(x[count]-avrx)*(y[count-tau]-avry);
        }
        if ( fabs(*CCC)<fabs(result[ylen-1+tau]) ){
            *CCC=result[ylen-1+tau];
            *shift=tau;
        }
    }

    *CCC/=energy;

    return 0;
}

int CC_static(double *x, int xlen, double *y, int ylen, double *CCC){

    int    count,xEnd;
    double energy,xx,yy;

    // Default error value;
    *CCC=0;

    // If signals are too short, return an error flag.
    if (xlen<=1 || ylen<=1){
        printf("In %s: Sequence too short !\n",__func__);
        return 1;
    }

    // Calculate x average and y average.
    double avrx=0,avry=0;
    for (count=0;count<xlen;count++){
        avrx+=x[count];
    }
    avrx/=xlen;
    for (count=0;count<ylen;count++){
        avry+=y[count];
    }
    avry/=ylen;

    // Denominator.
    xx=0;
    yy=0;
    for (count=0;count<xlen;count++){
        xx+=pow(x[count]-avrx,2);
    }
    for (count=0;count<ylen;count++){
        yy+=pow(y[count]-avry,2);
    }
    if ( sqrt(xx)< 1e-30 || sqrt(yy)< 1e-30 ){
        printf("In %s: Energy is zero !\n",__func__);
        return 2;
    }
    energy=sqrt(xx*yy);

    // Evaluating CCC at shift=0.
    xEnd=xlen<ylen?xlen:ylen;

    (*CCC)=0;
    for (count=0;count<xEnd;count++){
        (*CCC)+=(x[count]-avrx)*(y[count]-avry);
    }

    (*CCC)/=energy;

    return 0;
}

int CC_static_energy(double *x, int xlen, double *y, int ylen, double *CCC){

    int    count,xEnd;
    double energy,xx,yy;

    // Default error value;
    *CCC=0;

    // If signals are too short, return an error flag.
    if (xlen<=1 || ylen<=1){
        printf("In %s: Sequence too short !\n",__func__);
        return 1;
    }

    // Calculate x average and y average.
    double avrx=0,avry=0;
    for (count=0;count<xlen;count++){
        avrx+=x[count];
    }
    avrx/=xlen;
    for (count=0;count<ylen;count++){
        avry+=y[count];
    }
    avry/=ylen;

    // Denominator.
    xx=0;
    yy=0;
    for (count=0;count<xlen;count++){
        xx+=pow(x[count]-avrx,2);
    }
    for (count=0;count<ylen;count++){
        yy+=pow(y[count]-avry,2);
    }
    if ( sqrt(xx)< 1e-30 || sqrt(yy)< 1e-30 ){
        printf("In %s: Energy is zero !\n",__func__);
        return 2;
    }
    energy=sqrt(xx*yy);

    // Evaluating CCC at shift=0.
    xEnd=xlen<ylen?xlen:ylen;

    (*CCC)=0;
    for (count=0;count<xEnd;count++){
        (*CCC)+=(x[count]-avrx)*(y[count]-avry);
    }

    (*CCC)*=(sqrt(fmin(xx,yy)/fmax(xx,yy))/energy);

    return 0;
}

int CC_limitshift(double *x, int xlen, double *y, int ylen, int *shift, double *CCC, double TimeLimit, double delta){

    int    count,tau,Shift,xBegin,xEnd;
    double energy,xx,yy,R;

    // Default error value;
    *shift=xlen+ylen-1;
    *CCC=0;

    // If signals are too short, return an error flag.
    if (xlen<=1 || ylen<=1){
        printf("In %s: Sequence too short !\n",__func__);
        return 1;
    }

    // Calculate x average and y average.
    double avrx=0,avry=0;
    for (count=0;count<xlen;count++){
        avrx+=x[count];
    }
    avrx/=xlen;
    for (count=0;count<ylen;count++){
        avry+=y[count];
    }
    avry/=ylen;

    // Denominator.
    xx=0;
    yy=0;
    for (count=0;count<xlen;count++){
        xx+=pow(x[count]-avrx,2);
    }
    for (count=0;count<ylen;count++){
        yy+=pow(y[count]-avry,2);
    }
    if ( sqrt(xx)< 1e-30 || sqrt(yy)< 1e-30 ){
        printf("In %s: Energy is zero !\n",__func__);
        return 2;
    }
    energy=sqrt(xx*yy);

    // Shifting and evaluating CCC at every shift value (tau).

    Shift=(int)ceil(TimeLimit/delta);

    for (tau=-Shift;tau<=Shift;tau++){
        xBegin=tau>0?tau:0;
        xEnd=xlen<(ylen+tau)?xlen:(ylen+tau);

        R=0;
        for (count=xBegin;count<xEnd;count++){
            R+=(x[count]-avrx)*(y[count-tau]-avry);
        }
        if ( fabs(*CCC)<fabs(R) ){
            *CCC=R;
            *shift=tau;
        }
    }

    *CCC/=energy;

    return 0;
}
