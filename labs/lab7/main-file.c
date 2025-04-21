#include <stdio.h>
#include <string.h>

typedef struct  {
	
    char name[32];
    char surname[32];
    int age;
    
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
            if (hum[j].age > hum[j + 1].age)
                swap(hum, j, j + 1);
        }
    }
}

int main() {
	
	FILE *inputfile = fopen("input.txt", "r");
	
	if (inputfile == NULL) {
		printf("file opening error");
		fclose(inputfile);
	}
    
    Human input[4];
    Human sorted[4];
    
    char line[256];
    char name[32];
    char surname[32];
    int age;
    
    while (fgets(line, sizeof(line), inputfile)) {
	
        if (sscanf(line, "%s %s %d", name, surname, &age) == 3) {
        	
            //printf("%s %s %d\n", name, surname, age);
            
            int i;
    		for (i = 0; i < 4; i++) {
        		input[i].name[32] = *name;
				input[i].surname[32] = surname;
				input[i].age = age;
			}
		}
	}
	
	int i;
	for (i = 0; i < 4; i++) {
        printf("%s %s, %d\n", input[i].name, input[i].surname, input[i].age);
    }
    
    memcpy(sorted, input, sizeof(input));

	bubbleSort(sorted, 4);
	
	

    printf("\nSorted humans:\n");
    
    for (i = 0; i < 4; i++) {
        //printf("%s %s, %d\n", sorted[i].name, sorted[i].surname, sorted[i].age);
    }
    
    
    fclose(inputfile);
    return 0;
}
