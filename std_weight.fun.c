#include<stdio.h>
#include<math.h>
#include<ASU_tools.h>

/***********************************************************
 * This C function returns weighted standard deviation for
 * input array. The formula is :
 *
 * \sqrt{\dfrac{N'*\sum_{i=1}^N \omega_i*(x_i-\bar{x_w})^2}{(N'-1)\sum_{i=1}^N \omega_i}
 *
 * double *p    ----  Data pointer.
 * double *w    ----  Weight pointer.
 *                    negative weight means taking a negative value.
 * int    npts  ----  Array npts.
 *
 * Shule Yu
 * Sept 18 2014
 *
 * Note     : when weight!=0's record number <= 1 , return 0.
 *            In method 1, when weights=1, the std result is the same as std_d.
 *
 * Key words: standard deviation, weighted
 *
 * Reference:
 *
 *     Method 1: http://www.itl.nist.gov/div898/software/dataplot/refman2/ch2/weightsd.pdf
 *
 *     Method 2: http://www.analyticalgroup.com/download/WEIGHTED_MEAN.pdf
***********************************************************/

double std_weight(double *p, double *w, int npts){

	// Method 1.
    int    count,N;
    double flip,avrx,UP,W;

    N=0;
    W=0;
    for (count=0;count<npts;count++){
        W+=fabs(w[count]);
        if (w[count]!=0){
            N++;
        }
    }

    if (N<=1){
        return 0;
    }

    // Calculate x average.
    avrx=0;
    for (count=0;count<npts;count++){
        avrx+=w[count]*p[count];
    }
    avrx/=W;

    // Calculate summation.
    UP=0;
    for (count=0;count<npts;count++){
        flip=(w[count]>0?1:-1);
        UP+=flip*w[count]*pow(flip*p[count]-avrx,2);
    }

    // Return standard deviation.
    return sqrt(UP*N/(N-1)/W);

	// Method 2.
// 	int    count;
// 	double avrx,W,UpLeft;
//
//     W=0;
//     avrx=0;
// 	UpLeft=0;
//     for (count=0;count<npts;count++){
//         W+=fabs(w[count]);
//         avrx+=w[count]*p[count];
// 		UpLeft+=fabs(w[count])*pow(p[count],2);
//     }
//
// 	return sqrt((UpLeft-pow(avrx,2)/W)/(W-1));
}
