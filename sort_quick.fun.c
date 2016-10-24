#include<ASU_tools.h>

// 2 functions
// sort_quick
// sort_quickd
// sort_quick_i

/***********************************************************
 * This C function use quick sort algorithm to sort an input
 * array to ascending order.
 *
 * float/double *p    ----  Array pointer.
 * int          npts  ----  Array length.
 *
 * Shule Yu
 * Apr 02 2014
 *
 * Note: Orignal data destroyed.
 * Key words: sort, quick.
 *
 * Reference:
 *     http://en.wikipedia.org/wiki/Quicksort
***********************************************************/

void sort_quick(float *p, int npts){

    if (npts<2){
        return;
    }

    int    i,j;
    double key=p[0];

    i=0;
    j=npts-1;
    while ( i!=j ){

		while ( j>i && p[j]>key ){
            j--;
        }

		if ( j>i ){
			p[i]=p[j];
			i++;
		}

		while ( j>i && p[i]<key ){
            i++;
        }
		if ( j>i ){
			p[j]=p[i];
			j--;
		}
    }

    p[i]=key;
	sort_quick(p,i);
	sort_quick(p+i+1,npts-1-i);
}

void sort_quickd(double *p, int npts){

    if (npts<2){
        return;
    }

    int    i,j;
    double key=p[0];

    i=0;
    j=npts-1;
    while ( i!=j ){

		while ( j>i && p[j]>key ){
            j--;
        }

		if ( j>i ){
			p[i]=p[j];
			i++;
		}

		while ( j>i && p[i]<key ){
            i++;
        }
		if ( j>i ){
			p[j]=p[i];
			j--;
		}
    }

    p[i]=key;
	sort_quickd(p,i);
	sort_quickd(p+i+1,npts-1-i);
}

void sort_quick_i(int *p, int npts){

    if (npts<2){
        return;
    }

    int    i,j,key=p[0];

    i=0;
    j=npts-1;
    while ( i!=j ){

		while ( j>i && p[j]>key ){
            j--;
        }

		if ( j>i ){
			p[i]=p[j];
			i++;
		}

		while ( j>i && p[i]<key ){
            i++;
        }
		if ( j>i ){
			p[j]=p[i];
			j--;
		}
    }

    p[i]=key;
	sort_quick_i(p,i);
	sort_quick_i(p+i+1,npts-1-i);
}
