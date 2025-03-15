#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {

    double mat[3][3];
    for (int i = 0; i < 3; i++) {
	for (int j = 0; j < 3; j ++ ) {
        	scanf("%lf", &mat[i][j]);
	}
    }
////////////////////////////////////////////////////
	printf("\nMATRIX:\n");
	for (int i = 0; i < 3; i++) {
        	for (int j = 0; j < 3; j++) {
            		printf("%lf\t", mat[i][j], "/n");
        	}
        	printf("\n");
	}
	printf("\n");
////////////////////////////////////////////////////
    double suma;
	printf("SUM: \n");
	 for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            suma += mat[i][j];
        }}
    printf("%lf", suma, "\n"); printf("\n\n");
////////////////////////////////////////////////////
    double d1;
    printf("DIAGONAL 1: \n");
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (i == j) {
            d1 += mat[i][j];}

        }}
    printf("%lf", d1, "/n");
////////////////////////////////////////////////////
    double d2;
    printf("\n\nDIAGONAL 2: \n");
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (i+j == 2) {
            d2 += mat[i][j];}

        }}
    printf("%lf", d2, "/n"); printf("\n");

	return 0;
}
