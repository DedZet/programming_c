#include <stdio.h>
#include <stdlib.h>

#define FIND_MAX(arr, size) ({ \
	int max = arr[0]; \
	int i; \
	for (i = 1; i < size; ++i) { \
        if (arr[i] > max) { \
            max = arr[i]; \
        } \
    } \
    max; \
})

int main(int argc, char *argv[]) {
	
    int numbers[32];
    int count = 0;
    
    printf("Enter nums: ");

	while (scanf("%d", &numbers[count]) == 1 && getchar() != '\n') {
        count++;
    }
    
    int result = FIND_MAX(numbers, count);
    printf("Max: %d", result);
    
	return 0;
}
