#include <stdarg.h>

void swap(int arr[], int i) {
    int temp = arr[i];
    arr[i] = arr[i+1];
    arr[i+1] = temp;
}

int find_sum(int count, ...) {
    va_list args;
    int result = 0;
    
    va_start(args, count);
    
    int i;
    for (i = 0; i < count; i++) result += va_arg(args, int);
        
    va_end(args);
    return result;
}

int find_max(int count, ...) {
    va_list args;
    int result[count];
    
    va_start(args, count);
    
    
    int i, j;
    for(i = 0; i < count; i++) {
        result[i] = va_arg(args, int);
    }
    
    va_end(args);
    
    for (i = 0; i < count - 1; i++) {
    	for (j = 0; j < count - i - 1; j++) {
    		if (result[j] > result[j + 1]) {
    			swap(result, j);
			}
		}
	}
	
	va_end(args);
	
    return result[count-1];
}

int find_min(int count, ...) {
    va_list args;
    int result[count];
    
    va_start(args, count);
    
    int i, j;
    for(i = 0; i < count; i++) {
        result[i] = va_arg(args, int);
    }
    
    va_end(args);
    
    for (i = 0; i < count - 1; i++) {
    	for (j = 0; j < count - i - 1; j++) {
    		if (result[j] > result[j + 1]) {
    			swap(result, j);
			}
		}
	}
	
    return result[0];
}

int find_avr(int count, ...) {
    va_list args;
    int result = 0;
    
    va_start(args, count);
    
    int i;
    for (i = 0; i < count; i++) result += va_arg(args, int);

    va_end(args);
    
    return result / count;
}

