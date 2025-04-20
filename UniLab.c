#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

double discrim(double a, double b, double c) {
	return b*b-4*a*c;
}

void clear() {
	system("cls");
}

//*char upper_string(*char str) {
//	while (text[i]) {
//        ch = text[i];
//        putchar(toupper(ch));
//        i++;
//    }
//	return str;
//}

void print_matrix(double** matrix, int row, int col) {
	int i,j;
    for(i=0; i<row; i++){
        for(j=0; j<col; j++) {
           printf("%lf ", matrix[i][j]);
        }
        printf("\n");
    }
}

void free_matrix(double** matrix, int size) {
	int i;
    for (i = 0; i < size; i++) {
        free(matrix[i]);
    }
    free(matrix);
}

//double** create_dyn_matrix(int row, int col) {
//	double** mat = (double**)malloc(row * sizeof(double*));
//    
//    int i,j;
//    for (i = 0; i < row; i++) {
//    	mat[i] = (double*)malloc(col * sizeof(double));
//    	
//		for (j = 0; j < col; j++) {
//        	scanf("%lf", &mat[i][j]);
//		}
//    }
//}

void swap(int arr[], int i, int j) {
    int temp = arr[i];
    arr[i] = arr[j];
    arr[j] = temp;
}

int isvowel(char c) {// DOESNT WORK FOR CYRILLIC 
	switch(tolower(c)) {
		case 'a': 
		case 'e':
		case 'i': 
		case 'o': 
		case 'u':
		case 'y': return 1;
	}
	return 0;
}

void bubble_sort(int arr[], int size) {
    int i,j;
    for (i = 0; i < size - 1; i++) {
        for (j = 0; j < size - i - 1; j++) {
            if (arr[j] > arr[j + 1])
                swap(arr, j, j + 1);
        }
    }
}

int check_file(FILE *file) {
	if (file == NULL) {
		printf("File opening error");
		fclose(file);
	}
}


int main(int argc, char *argv[]) {
	SetConsoleOutputCP(CP_UTF8);
	
	//double** mat = create_dyn_matrix(2,2);
	//memcpy(sorted, input, sizeof(input)); // copy array from-to
	
	
	


	
	return 0;
}
