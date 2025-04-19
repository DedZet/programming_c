#include <stdio.h>
#include <string.h>
#include <math.h>

typedef struct  {
	
    char name[32];
    char surname[32];
    int age;
    
} Human;

int compare(Human a, Human b)
{
    return abs(a.age - b.age);
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

    int len = sizeof(input) / sizeof(input[0]);
    qsort(input, len, sizeof(Human), compare);
    
    printf("\nSorted humans:\n");
    for (i = 0; i < 4; i++) {
        printf("%s %s, %d\n", sorted[i].name, sorted[i].surname, sorted[i].age);
    }
    
    return 0;
}
