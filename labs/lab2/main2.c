#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {

	double x[4];
    for (int i = 0; i < 9; i++) {
        scanf("%lf", &x[i]);
    
    }

	double mat[2][2] = {
		{x[0],x[1]},
		{x[2],x[3]}};

////////////////////////////////////////////////////
	printf("\nMATRIX:\n");
	for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            printf("%i\t", mat[i][j], "/n");
        }
        printf("\n");
	} printf("\n");
    
////////////////////////////////////////////////////
    printf("\nMATRIX^2:\n");
    
    int mul[2][2] = {
        { mat[0][0]*mat[0][0] + mat[0][1]*mat[1][0], mat[0][0]*mat[0][1] + mat[0][1]*mat[1][1] },
        { mat[1][0]*mat[0][0] + mat[1][1]*mat[1][0], mat[1][0]*mat[0][1] + mat[1][1]*mat[1][1] },
    };
    
	for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            printf("%i\t", mul[i][j], "/n");
        }
        printf("\n");
	} 
	printf("\n");

	return 0;
}
