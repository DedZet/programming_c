#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <windows.h>


typedef struct {
	
	char name[32];
	char surname[32];
	int year;
	char gender;
	float height;
	
} Human;

void swap(Human hum[], int i, int j) {
    Human temp = hum[i];
    hum[i] = hum[j];
    hum[j] = temp;
}

void bubble_sort(Human hum[], int size) {
    int i,j;
    for (i = 0; i < size - 1; i++) {
        for (j = 0; j < size - i - 1; j++) {
            if (hum[j].year > hum[j + 1].year)
                swap(hum, j, j + 1);
        }
    }
}

int main(int argc, char *argv[]) {
	
	SetConsoleOutputCP(CP_UTF8);
	
//	Human* humans = (Human*) malloc(4*sizeof(Human));
//    Human* sorted = (Human*) malloc(4*sizeof(Human));
    
    int size = 16;
    Human humans[size];
    Human sorted[size];
	
	FILE *namesfile = fopen("names.txt","r");
		
	if (namesfile == NULL) {
		printf("File opening error");
		return 1;
	}
	
	
	
	int i;
    for (i = 0; i < size; i++) {
        fscanf(namesfile, "%s %s %d %c %f", humans[i].name, humans[i].surname, &humans[i].year, &humans[i].gender, &humans[i].height);
    }
    

	memcpy(sorted, humans, sizeof(humans));
	bubble_sort(sorted, size);

         
    for (i = 0; i < size; i++) {
        printf("%s %s %d %c %.2f\n", sorted[i].name, sorted[i].surname, sorted[i].year, sorted[i].gender, sorted[i].height);
    }
	
	
	return 0;
}
