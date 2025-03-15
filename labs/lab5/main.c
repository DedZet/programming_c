#include <stdio.h>
#include <math.h>
#include <stdbool.h>

// void printarr(double arr[], int n) {
//     for (int i = 0; i < n; i++) {
//         printf("%f ", arr[i]);
//     }
// }

void printmat(double mat[][], int r, int c) {
    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            printf("%lf\t", mat[i][j], "/n");
        }
    }
}

int typechoose() {
    printf("Matrix / Array");
    
    char ch;
    scanf("%c", &ch);
    
    if (toupper(ch) == "M") {
        return 0;
    }
    else if (toupper(ch) == "A") {
        return 1;
    }
    else { return 2; }
    
}

int main() {
    
    double x1,x2,x3,x4,x5,x6,x7,x8,x9;
    
    printf("First row \n");
    scanf("%lf %lf %lf", &x1, &x2, &x3);
    
    printf("Second row \n");
    scanf("%lf %lf %lf", &x4, &x5, &x6);
    
    printf("Third row \n");
    scanf("%lf %lf %lf", &x7, &x8, &x9);

	double matrix1[3][3] = {
		{x1,x2,x3}, 
		{x4,x5,x6}, 
		{x7,x8,x9}}; 
		
	double matrix2[3][3] = {
        {1,5,3},
        {4,4,4},
        {3,2,1}};
    
    double array1[] = {1,2,3,4,3};
    double array2[] = {1,6,5,4,3};

        
    printmat(matrix2,3,3);
    
    return 0;
}
    
    
    return 0;
}
