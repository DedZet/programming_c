#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    int x1,x2,x3,x4;
    x1 = 1;
    x2 = 3;
    x3 = 5;
    x4 = 4;
    // printf("First row \n");
    // scanf("%d %d %d", &x1, &x2);
    
    // printf("Second row \n");
    // scanf("%d %d %d", &x3, &x4);

	int mat[2][2] = {
		{x1,x2}, //6
		{x3,x4}, // 15
	};
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
