#include <stdio.h>
#include <string.h>
#include <locale.h>
#include <windows.h>

typedef struct  {
    char name[32];
    char surname[32];
    int year;
    
} Human;

void swap(Human hum[], int i, int j) {
    Human temp = hum[i];
    hum[i] = hum[j];
    hum[j] = temp;
}

void bubbleSort(Human hum[], int size) {
    int i,j;
    for (i = 0; i < size - 1; i++) {
        for (j = 0; j < size - i - 1; j++) {
            if (hum[j].year > hum[j + 1].year)
				swap(hum, j, j + 1);
        }
    }
}
	
int main() {
	SetConsoleOutputCP(CP_UTF8);
	
	FILE *inputfile = fopen("input.txt", "r");
	
	if (inputfile == NULL) {
		printf("file opening error");
		return 1;
	}
	
	int count = 1;
    char c;
	
	while ((c = fgetc(inputfile)) != EOF)
    {
        if ( c == '\n')
        {
            count++;
        }
    }
    
    fclose(inputfile);
    
	Human input[count];
    Human sorted[count];

    int i;
    
    char buffer[100];
    for (i = 0; i < count; i++) {
    	fgets(buffer, sizeof(buffer), inputfile);
        fscanf(inputfile, "%s %s %d", input[i].name, input[i].surname, &input[i].year);
    }
    
    fclose(inputfile);
    
    memcpy(sorted, input, sizeof(input));

	bubbleSort(sorted, count);
	
    printf("Sorted humans:\n");
    
    for (i = 0; i < count; i++) {
        printf("%s %s, %d\n", sorted[i].name, sorted[i].surname, sorted[i].year);
    }

    return 0;
}
