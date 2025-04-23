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

void read_file(FILE *filename, Human hums[], int fsize) {
	int c = 0;
    while (c < fsize && fscanf(filename, "%s %s %d %c %f", 
	hums[c].name, hums[c].surname, &hums[c].year, &hums[c].gender, &hums[c].height) == 5) {	
        c++;
    }
    fclose(filename);
}

///////////////////// SORT FUNCS //////////////////////////////

void bsort_year(Human hum[], int size) {
    int i,j;
    for (i = 0; i < size - 1; i++) {
        for (j = 0; j < size - i - 1; j++) {
            if (hum[j].year > hum[j + 1].year)
                swap(hum, j, j + 1);
        }
    }
}

void bsort_height(Human hum[], int size) {
    int i,j;
    for (i = 0; i < size - 1; i++) {
        for (j = 0; j < size - i - 1; j++) {
            if (hum[j].height > hum[j + 1].height)
                swap(hum, j, j + 1);
        }
    }
}



int compare_name(Human a, Human b) {
	return strcmp(a.name, b.name);
}

int compare_surname(Human a, Human b) {
	return strcmp(a.surname, b.surname);
}

int compare_gender(Human a, Human b) {
	if( a.gender < b.gender ) printf("%c is smaller than %c", a, b);
	if( a.gender > b.gender ) printf("%c is smaller than %c", a, b);
	if( a.gender == b.gender ) printf("%c is equal to %c", a, b);
	return 0;
}

///////////////////////////////////////////////////////////////


	
void logic(Human hum[], char chose) {
	
	int i = 0;
	Human hum_a = hum[i];
	Human hum_b = hum[i+1];
	
	scanf("%c", &chose);
	int result = 0;
	
	switch (chose) {
		case 'n': // name
			
			break;
			
		case 's': // surname
			
			break;
			
		case 'y': // year
			//bsort_year(hum, size);
			
		case 'g': // gender
			// result = strcmp(a.gender, b.gender);
			break;
			
		case 'h': // height
		break;
	}
}

int main(int argc, char *argv[]) {
	
	SetConsoleOutputCP(CP_UTF8);
	
    int size = 6;
    Human humans[size];
    Human sorted[size];
	
	FILE *namesfile = fopen("names.txt","r");
		
	if (namesfile == NULL) {
		printf("File opening error");
		return 1;
	}
	
	read_file(namesfile, humans, size);

	memcpy(sorted, humans, sizeof(humans));
	
	//bubble_sort(sorted, size);
	
	int i;
    for (i = 0; i < size; i++) {
        printf("%s %s %d %c %.2f\n", sorted[i].name, sorted[i].surname, sorted[i].year, sorted[i].gender, sorted[i].height);
    }
	
	
	return 0;
}
