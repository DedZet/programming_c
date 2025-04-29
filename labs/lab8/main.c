#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <windows.h>

#define GLSIZE 6

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

void rw_file(FILE *filename, Human hums[]) {
	int c = 0;
    while (c < GLSIZE && fscanf(filename, "%s %s %d %c %f", 
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

int compare_genf(Human a, Human b) {
	if( a.gender < b.gender ) return -1;
	if( a.gender > b.gender ) return 1;
	if( a.gender == b.gender ) return 0;
}

int compare_genm(Human a, Human b) {
	if( a.gender < b.gender ) return 1;
	if( a.gender > b.gender ) return -1;
	if( a.gender == b.gender ) return 0;
}

///////////////////////////////////////////////////////////////
	
Human *operations(Human hum[], char chose[]) {
	
	///////////// NOT COMBINED FILTERS /////////////
	
		if (strncmp(chose, "nn", 2) == 0)  // name
			qsort(hum, GLSIZE, sizeof(Human), compare_name);
			
		else if (strncmp(chose, "ss", 2) == 0) // surname
			qsort(hum, GLSIZE, sizeof(Human), compare_surname);
		
		else if (strncmp(chose, "yy", 2) == 0) // year
			bsort_year(hum, GLSIZE);
		
		else if (strncmp(chose, "ff", 2) == 0) // gender f
			qsort(hum, GLSIZE, sizeof(Human), compare_genf);
		
		else if (strncmp(chose, "mm", 2) == 0) // gender m
			qsort(hum, GLSIZE, sizeof(Human), compare_genm);
		
		else if (strncmp(chose, "hh", 2) == 0) // height
			bsort_height(hum, GLSIZE);
		
		/////////////// COMBINED FILTERS ///////////////
		
		//if (chose)
		
		
		
		
		
		
		
		
		////////////////// RETURNS ///////////////////
		
		else {
			printf("not an operation");
			return NULL;
		}
		
	return hum;
}
	

int main(int argc, char *argv[]) {
	
	SetConsoleOutputCP(CP_UTF8);
	
    Human humans[GLSIZE];
    Human sorted[GLSIZE];
    char chose[3];
	
	FILE *namesfile = fopen("names.txt","r");
		
	if (namesfile == NULL) {
		printf("File opening error");
		return 1;
	}
	
	rw_file(namesfile, humans);

	memcpy(sorted, humans, sizeof(humans));
	
	printf("Enter filters (n,s,y,f,m,h) ");
	scanf("%2s", chose);
	
	Human *copy = operations(sorted, chose);
	
	if (copy == NULL) {
		fclose(namesfile);
		return 1;
	}
	
	system("cls");
	
	int i;
    for (i = 0; i < GLSIZE; i++) {
        printf("%s %s %d %c %.2f\n", copy[i].name, copy[i].surname, copy[i].year, copy[i].gender, copy[i].height);
    }
	
	return 0;
}
