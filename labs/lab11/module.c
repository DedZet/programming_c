#include <stdio.h>
#include <stdlib.h>

int find_sum(int arr[], int size) {
	int sum = 0;
	int i;
	for (i = 0; i < size+1; ++i) {
		sum += arr[i];
        }
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

	
