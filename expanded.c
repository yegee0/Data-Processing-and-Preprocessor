#include "P_header.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(){

    int A[2];
    //
    int B[2];
    //
    for (int i = 0; i < (int)(sizeof(A)/sizeof(A[0])); i++) {
        A[i] = 3;
    }
    //
    for (int i = 0; i < (int)(sizeof(A)/sizeof(A[0])); i++) {
        printf("%d ", A[i]);
    }
    printf("\n");
    printf("\n");
    //
    FILE *filedata = fopen("../data", "r");
    for (int i = 0; i < (int)(sizeof(B)/sizeof(B[0])); i++) {
        fscanf(filedata, "%d", &B[i]);
    }
    fclose(filedata);
    //
    for (int i = 0; i < (int)(sizeof(B)/sizeof(B[0])); i++) {
        printf("%d ", B[i]);
    }
    printf("\n");
    printf("\n");
    //
    for (int i = 0; i < (int)(sizeof(A)/sizeof(A[0])); i++) {
        B[i] = A[i];
    }
    //
    for (int i = 0; i < (int)(sizeof(B)/sizeof(B[0])); i++) {
        printf("%d ", B[i]);
    }
    printf("\n");
    printf("\n");
    //
    P_dot = 0;
    for (int i = 0; i < (int)(sizeof(A)/sizeof(A[0])); i++) {
        P_dot += A[i] * B[i];
    }
    //
    printf("Result of dotp is %d", P_dot);
    printf("\n");
    //
    int C[2];
    //
    for (int i = 0; i < (int)(sizeof(A)/sizeof(A[0])); i++) {
        C[i] = A[i] + B[i];
    }
    //
    for (int i = 0; i < (int)(sizeof(C)/sizeof(C[0])); i++) {
        printf("%d ", C[i]);
    }
    printf("\n");
    //
    P_sum = 0;
    for (int i = 0; i < (int)(sizeof(A)/sizeof(A[0])); i++) {
        P_sum += A[i];
    }
    //
    printf("Result of sum is %d", P_sum);
    printf("\n");
    //
    P_aver = 0;
    int total_elementsA = 0;
    for (int i = 0; i < (int)(sizeof(A)/sizeof(A[0])); i++) {
        P_aver += A[i];
        total_elementsA++;
    }
    if (total_elementsA > 0) {
        P_aver /= total_elementsA;
    }
    //
    printf("Result of aver is %d", P_aver);
    printf("\n");

    //
    printf("\nEnd of 1D Tests\n");
    //

    int D[3][3];
    //
    int E[3][3];
    //
    for (int i = 0; i < (int)(sizeof(D)/sizeof(D[0])); i++) {
        for (int j = 0; j < (int)(sizeof(D[0])/sizeof(D[0][0])); j++) {
            D[i][j] = 5;
        }
    }
    //
    for (int i = 0; i < (int)(sizeof(D)/sizeof(D[0])); i++) {
        for (int j = 0; j < (int)(sizeof(D[0])/sizeof(D[0][0])); j++) {
            printf("%d ", D[i][j]);
        }
        printf("\n");
    }
    printf("\n");
    //
    for (int i = 0; i < (int)(sizeof(D)/sizeof(D[0])); i++) {
        for (int j = 0; j < (int)(sizeof(D[0])/sizeof(D[0][0])); j++) {
            E[i][j] = D[i][j];
        }
    }
    //
    for (int i = 0; i < (int)(sizeof(E)/sizeof(E[0])); i++) {
        for (int j = 0; j < (int)(sizeof(E[0])/sizeof(E[0][0])); j++) {
            printf("%d ", E[i][j]);
        }
        printf("\n");
    }
    printf("\n");
    //
    FILE *filedata2 = fopen("../data2", "r");
    for (int i = 0; i < (int)(sizeof(D)/sizeof(D[0])); i++) {
        for (int j = 0; j < (int)(sizeof(D[0])/sizeof(D[0][0])); j++) {
            fscanf(filedata2, "%d", &D[i][j]);
        }
    }
    fclose(filedata2);
    //
    for (int i = 0; i < (int)(sizeof(D)/sizeof(D[0])); i++) {
        for (int j = 0; j < (int)(sizeof(D[0])/sizeof(D[0][0])); j++) {
            printf("%d ", D[i][j]);
        }
        printf("\n");
    }
    printf("\n");
    //
    int F[3][3];
    //
    for (int i = 0; i < (int)(sizeof(D)/sizeof(D[0])); i++) {
        for (int j = 0; j < (int)(sizeof(D[0])/sizeof(D[0][0])); j++) {
            F[i][j] = D[i][j] + E[i][j];
        }
    }
    //
    for (int i = 0; i < (int)(sizeof(F)/sizeof(F[0])); i++) {
        for (int j = 0; j < (int)(sizeof(F[0])/sizeof(F[0][0])); j++) {
            printf("%d ", F[i][j]);
        }
        printf("\n");
    }
    printf("\n");
    //
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            F[i][j] = 0;
            for (int k = 0; k < 3; k++) {
                F[i][j] += D[i][k] * E[k][j];
            }
        }
    }
    //
    for (int i = 0; i < (int)(sizeof(F)/sizeof(F[0])); i++) {
        for (int j = 0; j < (int)(sizeof(F[0])/sizeof(F[0][0])); j++) {
            printf("%d ", F[i][j]);
        }
        printf("\n");
    }
    printf("\n");
    //
    P_sum = 0;
    for (int i = 0; i < (int)(sizeof(E)/sizeof(E[0])); i++) {
        for (int j = 0; j < (int)(sizeof(E)/sizeof(E[0])); j++) {
            P_sum += E[i][j];
        }
    }
    //
    printf("Result of sum is %d", P_sum);
    printf("\n");
    //
    P_aver = 0;
    int total_elementsE = 0;
    for (int i = 0; i < (int)(sizeof(E)/sizeof(E[0])); i++) {
        for (int j = 0; j < (int)(sizeof(E)/sizeof(E[0])); j++) {
            P_aver += E[i][j];
            total_elementsE++;
        }
    }
    if (total_elementsE > 0) {
        P_aver /= total_elementsE;
    }
    //
    printf("Result of aver is %d", P_aver);
    printf("\n");

    //
    printf("\nEnd of 2D Tests\n");
    //
}