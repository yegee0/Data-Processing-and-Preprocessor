#include "P_header.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(){

    @int A(2)
    //
    @int B(2)
    //
    @init A = 3
    //
    @print A
    printf("\n");
    //
    @read B < data
    //
    @print B
    printf("\n");
    //
    @copy B = A
    //
    @print B
    printf("\n");
    //
    @dotp C = A . B
    //
    printf("Result of dotp is %d", P_dot);
    printf("\n");
    //
    @int C(2)
    //
    @add C = A + B
    //
    @print C
    //
    @sum A
    //
    printf("Result of sum is %d", P_sum);
    printf("\n");
    //
    @aver A
    //
    printf("Result of aver is %d", P_aver);
    printf("\n");

    //
    printf("\nEnd of 1D Tests\n");
    //

    @int D(3,3)
    //
    @int E(3,3)
    //
    @init D = 5
    //
    @print D
    printf("\n");
    //
    @copy E = D 
    //
    @print E 
    printf("\n");
    //
    @read D < data2 
    //
    @print D
    printf("\n");
    //
    @int F(3,3)
    //
    @add F = D + E
    //
    @print F
    printf("\n");
    //
    @mmult F = D * E
    //
    @print F
    printf("\n");
    //
    @sum E
    //
    printf("Result of sum is %d", P_sum);
    printf("\n");
    //
    @aver E
    //
    printf("Result of aver is %d", P_aver);
    printf("\n");

    //
    printf("\nEnd of 2D Tests\n");
    //
}