#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

int find_sum(int num, ...) {
	
	int sum = 0;
	va_list list;
	va_start(list, num);
	
	while (num) {
		
		sum += va_arg(list, int);
		--num;
	}
	
	va_end(list);
    return sum;
}

int find_max(int arr[], int size) {
	int max = arr[0];
	int i;
	for (i = 0; i < size+1; ++i) {
        if (arr[i] > max) {
            max = arr[i];
        }
    }
    return max; 
}

int find_min(int arr[], int size) {
	int min = arr[0];
	int i;
	for (i = 0; i < size+1; i++) {
        if (arr[i] < min) {
            min = arr[i]; 
        } 
    } 
    return min; 
}

int find_avr(int arr[], int size) {
	int sum = find_sum(arr, size);
	return sum/(size+1);
}

	
