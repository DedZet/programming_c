#include <stdio.h>
#include <string.h>
#include <math.h>

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
    
    Human input[4];
    Human sorted[4];
    
    int i, j;
    for (i = 0; i < 4; i++) {
        printf("Enter Human %d ", i + 1);
        scanf("%s %s %d", &input[i].name, &input[i].surname, &input[i].age);
    }
    
    memcpy(sorted, input, sizeof(input));

	bubbleSort(sorted, 4);

    
    printf("\nSorted humans:\n");
    for (i = 0; i < 4; i++) {
        printf("%s %s, %d\n", sorted[i].name, sorted[i].surname, sorted[i].age);
    }
    
    return 0;
}
