#include "matrix.h"

int main() {
    
	int r,c;
    printf("enter rows for M1: ");
    scanf("%i", &r);
    printf("enter columns for M1: ");
    scanf("%i", &c);
    
    double mat[r][c];
    
    int i,j;
    for (i = 0; i < r; i++) {
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
    double mat2[r2][c2];
    
    int k,l;
    for (k = 0; k < r2; k++) {
	for (l = 0; l < c2; l++) {
        	scanf("%lf", &mat2[k][l]);
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
	
    return 0;
    
	}
