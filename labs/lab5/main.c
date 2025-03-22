#include <stdio.h>

void printMatrix(int row, int col, double m[row][col]) {
    for(int i=0; i<row; i++){
        for(int j=0; j<col; j++) {
           printf("%lf ", m[i][j]); 
        }
        printf("\n");
    }
}

double* makemat(int r, int c) {

    double* ptr = malloc((r * c) * sizeof(double));
    for (int i = 0; i < r * c; i++) {
        ptr[i] = i + 1;
    }
    
    return ptr;
}

int main() {
    
    int r,c;
    printf("enter rows");
    scanf("%i", &r);
    scanf("%i", &c);

    printMatrix(r,c,makemat(r,c));

    return 0;
}
