#include<stdio.h>
#include<stdlib.h>
#include<ASU_tools.h>

int main(){

    int   nx=5,ny=9,pad[4]={2,2,2,2};
    float p[45];
    float *pp;

    pp=(float *)malloc((nx+pad[0]+pad[1])*(ny+pad[2]+pad[3])*sizeof(float));

    int count;
    for (count=0;count<45;count++){
        p[count]=count+1;
    }


    printf("Original Ordering: \n");
    print_2d_array_f(p,nx,ny);

    // Use function.
    gmttrans_f(p,5,9,pp,pad);

    printf("GMT Ordering: \n");
//     print_2d_array_f(pp,nx+pad[0]+pad[1],ny+pad[2]+pad[3]);
    print_2d_array_f(pp,ny+pad[2]+pad[3],nx+pad[0]+pad[1]);

    return 0;
}
