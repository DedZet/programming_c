#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define FIND_MAX(arr, size) ({ \
	int max = arr[0]; \
	int i; \
	for (i = 0; i < size+1; ++i) { \
        if (arr[i] > max) { \
            max = arr[i]; \
        } \
    } \
    max; \
})

#define FIND_AVERAGE(arr, size) ({ \
	int sum = 0; \
	int i; \
	for (i = 0; i < size+1; i++) { \
		sum = sum + arr[i]; \
	} \
	double result = sum / (size+1); \
	result; \
})

int main(int argc, char *argv[]) {
	
    int numbers[32];
    int count = 0;
    
    printf("Enter nums: ");

	while (scanf("%d", &numbers[count]) == 1 && getchar() != '\n') {
        count++;
    }
    
    int result_max = FIND_MAX(numbers, count);
    int result_avr = FIND_AVERAGE(numbers, count);
    
    printf("Max: %d\nAverage: %d", result_max, result_avr);
    
    
	return 0;
}
