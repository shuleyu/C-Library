#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<ASU_tools.h>

// 2 functions:
// mixsize
// mixthem

/***********************************************************
 * This C function returns the mixing size of input series:
 *
 * ( min / max / inc ) * n
 *
 * double *p     ----  Input array pointer.
 * int    NPTS   ----  size of p = 3n.
 *
 * Shule Yu
 * Oct 21 2015
 *
 * Key words: mixing size.
***********************************************************/

int  mixsize(double *p, int NPTS){

    if (NPTS%3!=0){
        printf("In %s: Input size should be multiper of 3 ...\n",__func__);
        return -1;
    }

    int ans,Cnt;

    ans=1;

    for (Cnt=0;Cnt<NPTS/3;++Cnt){
        if (p[3*Cnt+1]>p[3*Cnt]){
            ans*=(1+(int)floor((p[3*Cnt+1]-p[3*Cnt]+1e-7)/p[3*Cnt+2]));
        }
    }
    return ans;
}

/************************************************************
 * This C function returns the mixing result of input series:
 *
 * ( min / max / inc ) * n
 *
 * double *p     ----  Input array pointer.
 * int    NPTS   ----  size of p.
 * double **res  ----  Output 2D array pointer.
 *                     Size: ( mixing size * NPTS/3 )
 *
 * Shule Yu
 * Oct 21 2015
 *
 * Key words: mixing result.
************************************************************/

void mixthem(double *p, int NPTS, double **res){

    if (NPTS%3!=0){
        printf("In %s: Input size should be multiper of 3 ...\n",__func__);
    }

    int    Cnt,Cnt2,Cnt3,Size;
    double tmpvar,**pp;

    if (NPTS==3){

        Cnt=0;
        tmpvar=p[0];
        while (Cnt==0 || tmpvar<p[1]+p[2]/2){
            res[Cnt][0]=tmpvar;
            ++Cnt;
            tmpvar+=p[2];
        }
        return;
    }

    Size=mixsize(p+3,NPTS-3);
    pp=(double **)malloc(Size*sizeof(double *));
    for (Cnt=0;Cnt<Size;Cnt++){
        pp[Cnt]=(double *)malloc((NPTS/3-1)*sizeof(double));
    }

    mixthem(p+3,NPTS-3,pp);

    Cnt=0;
    tmpvar=p[0];
    while (Cnt==0 || tmpvar<p[1]+p[2]/2){
        for (Cnt2=0;Cnt2<Size;Cnt2++){
            res[Cnt+Cnt2][0]=tmpvar;
            for (Cnt3=0;Cnt3<NPTS/3-1;Cnt3++){
                res[Cnt+Cnt2][1+Cnt3]=pp[Cnt2][Cnt3];
            }
        }
        Cnt+=Size;
        tmpvar+=p[2];
    }

    for (Cnt=0;Cnt<Size;Cnt++){
        free(pp[Cnt]);
    }
    free(pp);

    return;
}
