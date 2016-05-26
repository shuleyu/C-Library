#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ASU_tools.h>

int main(){
    
	int    Cnt,npts,res;
    double EVLO,EVLA,EVDP,STLO,STLA,depth,**ans;
    char   P[10];

    strcpy(P,"ScS");
    EVLO=0.0;
    EVLA=0.0;
    EVDP=500.00;

    STLO=0.0;
    STLA=70.0;

    depth=2861;

	npts=7100;
	ans=(double **)malloc(npts*sizeof(double *));
	for (Cnt=0;Cnt<npts;Cnt++){
		ans[Cnt]=(double *)malloc(3*sizeof(double));
	}

    // Use function.
	res=waypoint_sectionpath(P,EVLO,EVLA,EVDP,STLO,STLA,depth,npts,ans);
	printf("Res:%d\n",res);

    if ( res < 0 ){
        printf("Phase doesn't exist !\n");
    }
    else {
		for (Cnt=0;Cnt<res;Cnt++){
			printf("Lon/Lat/Depth: %11.3lf%11.3lf%11.2lf\n",ans[Cnt][0],ans[Cnt][1],ans[Cnt][2]);
		}
    }
    
    return 0;    
}
