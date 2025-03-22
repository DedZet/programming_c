#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    
    int scale;
    printf("Enter sq scale\n");
    scanf("%i", &scale);

	double mat[scale][scale];
	for (int i = 0; i < scale; i++) {
	    for (int j = 0; j < scale; j++) {
        	scanf("%lf", &mat[i][j]);
	    }
    }

////////////////////////////////////////////////////

	printf("\nMATRIX:\n");
	for (int i = 0; i < scale; i++) {
        for (int j = 0; j < scale; j++) {
            printf("%lf\t", mat[i][j], "/n");
        }
        printf("\n");
	} printf("\n");
    
////////////////////////////////////////////////////

    printf("\nMATRIX^2:\n");
    
    int mul[scale][scale];
	for (int i = 0; i < scale; i++) {
	    for (int j = 0; j < scale; j++) {
	        mul[i][j] = 0;
	        
	        for (int k = 0; k < scale; k++)
        	mul[i][j] += mat[i][k]*mat[k][j];
	    }
    }
    
	for (int i = 0; i < scale; i++) {
        for (int j = 0; j < scale; j++) {
            printf("%i\t", mul[i][j], "/n");
        }
        printf("\n");
	} 
	printf("\n");
	
	return 0;
}
