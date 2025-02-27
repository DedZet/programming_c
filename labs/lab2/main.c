#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    double x1,x2,x3;
    x2 = 3;
    x3 = 5;
    scanf("%lf", " %lf", "  %lf", &x1, &x2, &x3);
    
	double mat[3][3] = {
		{x1,x2,x3}, //6
		{4,5,6}, // 15
		{7,8,9}}; // 24 
////////////////////////////////////////////////////
	printf("MATRIX:\n");
	for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            printf("%lf\t", mat[i][j], "/n");
        }
        printf("\n");} printf("\n");
////////////////////////////////////////////////////
//     double suma;
// 	printf("SUM: \n");
// 	 for (int i = 0; i < 3; i++) {
//         for (int j = 0; j < 3; j++) {
//             suma += mat[i][j];
//         }}
//     printf("%lf", suma, "\n"); printf("\n\n");
////////////////////////////////////////////////////
    // double d1;
    // printf("DIAGONAL 1: \n");
    // for (int i = 0; i < 3; i++) {
    //     for (int j = 0; j < 3; j++) {
    //         if (i == j) {
    //         d1 += mat[i][j];}

    //     }}
    // printf("%lf", d1, "/n");
////////////////////////////////////////////////////
    // double d2;
    // printf("\n\nDIAGONAL 2: \n");
    // for (int i = 0; i < 3; i++) {
    //     for (int j = 0; j < 3; j++) {
    //         if (i+j == 2) {
    //         d2 += mat[i][j];}

    //     }}
    // printf("%lf", d2, "/n"); printf("\n");

	return 0;
}
