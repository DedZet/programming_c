#include <stdio.h>
#include <math.h>
#include <stdbool.h>

// void printarr(double arr[], int n) {
//     for (int i = 0; i < n; i++) {
//         printf("%f ", arr[i]);
//     }
// }


void printMatrix(int row, int col, double m[row][col]) {
    for(int i=0; i<row; i++){
        for(int j=0; j<col; j++)
            printf("%.2lf ", m[i][j]);
        printf("\n");
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

        
    printMatrix(3,3,matrix2);
    
    return 0;
}
    
    
    return 0;
}
