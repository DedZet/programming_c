#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <windows.h>

#define GLSIZE 16

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

//void bsort_year(Human hum[], int size) {
//    int i,j;
//    for (i = 0; i < size - 1; i++) {
//        for (j = 0; j < size - i - 1; j++) {
//            if (hum[j].year > hum[j + 1].year)
//                swap(hum, j, j + 1);
//        }
//    }
//}
//
//void bsort_height(Human hum[], int size) {
//    int i,j;
//    for (i = 0; i < size - 1; i++) {
//        for (j = 0; j < size - i - 1; j++) {
//            if (hum[j].height > hum[j + 1].height)
//                swap(hum, j, j + 1);
//        }
//    }
//}

int compare_name(Human a, Human b) {
	return strcmp(a.name, b.name);
}

int compare_surname(Human a, Human b) {
	return strcmp(a.surname, b.surname);
}

int compare_year(Human a, Human b) {
    if (a.year < a.year) return -1;
    if (a.year > a.year) return 1;
    if (a.year == a.year) return 0;
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

int compare_height(Human a, Human b) {
    if (a.height < a.height) return -1;
    if (a.height > a.height) return 1;
    if (a.height == a.height) return 0;
}

///////////////////////////////////////////////////////////////

char chose[3];
int combo_compare(Human a, Human b) {
	
	int result = 0;
	char field1 = chose[0];
	char field2 = chose[1];
	
	if (field1 == 'n')
        result = compare_name(a, b);
        
    else if (field1 == 's')
    	result = compare_surname(a, b);
    	
    else if (field1 == 'f')
        result = compare_genf(a, b);
        
    else if (field1 == 'm')
        result = compare_genm(a, b);
        
    else if (field1 == 'y')
        result = compare_year(a, b);
            
    else if (field1 == 'h')
        result = compare_height(a, b);
        
    // field 2
    
    if (result == 0) {
    	
        if (field2 == 'n')
            result = compare_name(a, b);
            
        else if (field2 == 's')
            result = compare_surname(a, b);
            
        else if (field2 == 'f') 
            result = compare_genf(a, b);
            
        else if (field2 == 'm')
            result = compare_genm(a, b);
            
        else if (field2 == 'y') 
            result = compare_year(a, b);
            
        else if (field2 == 'h')
            result = compare_height(a, b);

	}	
//
//	else {
//			printf("not an operation");
//			return result;
//		}
		
	return result;
}


///////////////////////////////////////////////////////////////
	
Human *operations(Human hum[], char chose[]) {
	
	Human buffer[GLSIZE];
	memcpy(buffer, hum, sizeof(hum));
	
	///////////// NOT COMBINED FILTERS /////////////
	
	if (strncmp(chose, "nn", 2) == 0)   // name
		qsort(hum, GLSIZE, sizeof(Human), compare_name);
	
	else if (strncmp(chose, "ss", 2) == 0) // surname
		qsort(hum, GLSIZE, sizeof(Human), compare_surname);
		
	else if (strncmp(chose, "yy", 2) == 0) // year
		qsort(hum, GLSIZE, sizeof(Human), compare_year);
		
	else if (strncmp(chose, "ff", 2) == 0) // gender f
		qsort(hum, GLSIZE, sizeof(Human), compare_genf);
		
	else if (strncmp(chose, "mm", 2) == 0) // gender m
		qsort(hum, GLSIZE, sizeof(Human), compare_genm);
		
	else if (strncmp(chose, "hh", 2) == 0) // height
		qsort(hum, GLSIZE, sizeof(Human), compare_height);
		
		/////////////// COMBINED FILTERS ///////////////
		
	else qsort(hum, GLSIZE, sizeof(Human), combo_compare);
		
		////////////////// RETURNS ///////////////////
		
	return hum;
}

int main(int argc, char *argv[]) {
	
	SetConsoleOutputCP(CP_UTF8);
	
    Human humans[GLSIZE];
    Human sorted[GLSIZE];
    
	
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
