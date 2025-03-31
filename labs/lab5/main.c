#include "matrix.h"

int main() {
    
	int r,c;
    printf("enter rows for M1: ");
    scanf("%i", &r);
    printf("enter columns for M1: ");
    scanf("%i", &c);
    
    double** mat = (double**)malloc(r * sizeof(double*));
    
    int i,j;
    for (i = 0; i < r; i++) {
    	mat[i] = (double*)malloc(c * sizeof(double));
    	
		for (j = 0; j < c; j++) {
        	scanf("%lf", &mat[i][j]);
		}
    }
    
    system("cls");
    //////////////////////////////////////
    
    int r2,c2;
    printf("enter rows for M2: ");
    scanf("%i", &r2);
    printf("enter columns for M2: ");
    scanf("%i", &c2);

    double** mat2 = (double**)malloc(r2 * sizeof(double*));
    // proverka
    for (i = 0; i < r; i++) {
    	mat2[i] = (double*)malloc(c2 * sizeof(double));
    	
		for (j = 0; j < c2; j++) {
        	scanf("%lf", &mat2[i][j]);
		}
    }
    
	system("cls");
	//////////////////////////////////////

    printMatrix(r,c,mat);
    printf("\n");
	printMatrix(r2,c2,mat2);

	char op;
	printf("\nenter operation: ");
    scanf(" %c", &op);

	matrix_op(r,c,r2,c2,mat,mat2,op);
	
	free_matrix(mat, r);
	free_matrix(mat2, r2);
	
    return 0;
    
	}
