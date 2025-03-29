#include <stdio.h>

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

void makemat(char text[2]) {

}

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
    
    //////////////////////////////////////
    system("cls");
    
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
    printMatrix(r,c,mat);
    printf("\n");
	printMatrix(r2,c2,mat2);

	char op;
	printf("\nenter operation: ");
    scanf(" %c", &op);

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
			free(op);
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
				printf("%d",c2);
				double mul[r2][c2];
				int i,j,k =0;

				for (i = 0; i < r; i++) {
	    			for (j = 0; j < c2; j++) {
	        			mul[i][j] = 0;
	        
	        			for (k = 0; k < c2; k++) {
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
	
    return 0;
	}
}
