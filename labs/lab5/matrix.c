#include <stdlib.h>
#include <stdio.h>
#include "matrix.h"

void printMatrix(int row, int col, double** m) {
	int i;
    for(i=0; i<row; i++){
    	int j;
        for(j=0; j<col; j++) {
           printf("%lf ", m[i][j]);
        }
        printf("\n");
    }
}

void free_matrix(double** matrix, int n) {
	int i;
    for (i = 0; i < n; i++) {
        free(matrix[i]);
    }
    free(matrix);
}


void matrix_op(int r, int c, int r2, int c2, double** mat, double** mat2, char op) {
	
    double** result = (double**)malloc(r2 * sizeof(double*));
    
    int i,j;
    for (i = 0; i < r2; i++) {
    		result[i] = (double*)malloc(r2 * sizeof(double));
		}
    
    
    switch (op) {
		case '+':
			if (r==r2 && c==c2) { 

				int i,j;
	 			for (i = 0; i < r; i++) {
        			for (j = 0; j < c; j++) {
            			result[i][j] = mat[i][j] + mat2[i][j];
        				}
				}
				
				printMatrix(r,c,result);
			}
			else {
				printf("Matrix size error");
			}
			break;
			
		case '-':
			if (r==r2 && c==c2) {

				int i,j;
	 			for (i = 0; i < r; i++) {
        			for (j = 0; j < c; j++) {
            			result[i][j] = mat[i][j] - mat2[i][j];
        				}
				}
				
				printMatrix(r,c,result);
			}
			else {
				printf("Matrix size error");
			}
			break;
			
		case '*':
			if ((r==r2 && c==c2) || (r2==c)) {
				int i,j,k = 0;

				for (i = 0; i < r2; i++) {
	    			for (j = 0; j < c2; j++) {
	        			result[i][j] = 0;
	        
	        			for (k = 0; k < r2; k++) {
        					result[i][j] += mat[i][k]*mat2[k][j];
        				}
	    			}
    			}
				
				printMatrix(r,c2,result);
			}
			else {
				printf("Matrix size error");
			}
			break;
			
		default:
			printf("Not an operation\n");

	}
	
	free_matrix(result, r2);
}
	

