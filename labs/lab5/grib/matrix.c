#include <stdlib.h>
#include <stdio.h>
#include "matrix.h"

void printMatrix(int row, int col, double m[row][col]) {
	int i;
    for(i=0; i<row; i++){
    	int j;
        for(j=0; j<col; j++) {
           printf("%lf ", m[i][j]); 
        }
        printf("\n");
    }
}

void matrix_op(int r, int c, int r2, int c2, double mat[r][c], double mat2[r2][c2], char op) {
	
    double** result = (double**)malloc(n * sizeof(double*));
    
    switch (op) {
		case '+':
			if (r==r2 && c==c2) { 
				double suma[r][c];

				int i,j;
	 			for (i = 0; i < r; i++) {
        			for (j = 0; j < c; j++) {
            			suma[i][j] = mat[i][j] + mat2[i][j];
        				}
				}
				
				printMatrix(r,c,suma);
			}
			else {
				printf("Matrix size error");
			}
			break;
			
		case '-':
			if (r==r2 && c==c2) {
				double sub[r][c];

				int i,j;
	 			for (i = 0; i < r; i++) {
        			for (j = 0; j < c; j++) {
            			sub[i][j] = mat[i][j] - mat2[i][j];
        				}
				}
				
				printMatrix(r,c,sub);
			}
			else {
				printf("Matrix size error");
			}
			break;
			
		case '*':
			if ((r==r2 && c==c2) || (r2==c)) {
				double mul[r2][c2];
				int i,j,k = 0;

				for (i = 0; i < r2; i++) {
	    			for (j = 0; j < c2; j++) {
	        			mul[i][j] = 0;
	        
	        			for (k = 0; k < r2; k++) {
        					mul[i][j] += mat[i][k]*mat2[k][j];
        				}
	    			}
    			}
				
				printMatrix(r,c2,mul);
			}
			else {
				printf("Matrix size error");
			}
			break;
			
		default:
			printf("Not an operation\n");

		}
	}
void free_matrix(double** matrix, int n) {
	int i;
    for (i = 0; i < n; i++) {
        free(matrix[i]);
    }
    free(matrix);
}

