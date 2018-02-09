#include<stdio.h>
#include<math.h>
#include<ASU_tools.h>

/***********************************************************
 * This C function returns standard deviation for input
 * array. The formula is :
 *
 * sigma=sqrt{ sum( (x-avr(x))^2 ) ) /(NPTS-1) }
 *
 * double *p    ----  Data pointer.
 * double *w    ----  Weight pointer.
 *                    negative weight means taking a negative value.
 * int    npts  ----  Array npts.
 *
 * Shule Yu
 * Sept 18 2014
 *
 * Note: when there's not enough record, we return 0 as
 *       estimation of sigma and gives a warning.
 *
 * Key words: standard deviation, unbiased, weighted
 *
 * Reference:
 * 	   Use SPSS approach for weighted standard deviation:
 *     http://www.analyticalgroup.com/download/WEIGHTED_MEAN.pdf
***********************************************************/

double std_weight(double *p, double *w, int npts){

	// Method 1.
//     int    count,N;
//     double flip,avrx,UP,W;
// 
//     N=0;
//     W=0;
//     for (count=0;count<npts;count++){
//         W+=fabs(w[count]);
//         if (w[count]!=0){
//             N++;
//         }
//     }
// 
//     if (N<=1){
//         return 0;
//     }
// 
//     // Calculate x average.
//     avrx=0;
//     for (count=0;count<npts;count++){
//         avrx+=w[count]*p[count];
//     }
//     avrx/=W;
// 
//     // Calculate summation.
//     UP=0;
//     for (count=0;count<npts;count++){
//         flip=(w[count]>0?1:-1);
//         UP+=flip*w[count]*pow(flip*p[count]-avrx,2);
//     }
// 
//     // Return standard deviation.
//     return sqrt(UP*N/(N-1)/W);

	// Method 2.
	double SumW=0,avr=0;
	for (size_t i=0;i<npts;++i){
		SumW+=fabs(w[i]);
		avr+=w[i]*p[i];
	}

	if (SumW<=0) {
		printf("In %s; Error: weight sum <= 0 ...\n",__func__ );
		return 0;
	}

	avr/=SumW;

	if (SumW<=1) {
		printf("In %s; Warning: weight sum <= 1 ...\n",__func__ );
		return 0;
	}
	double Sum=0;
	for (size_t i=0;i<npts;++i){
		double diff=(w[i]>0?1:-1)*p[i]-avr;
		Sum+=fabs(w[i])*diff*diff;
	}

	return sqrt(Sum/(SumW-1));
}
