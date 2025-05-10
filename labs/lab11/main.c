#include "module.h"


int main(int argc, char *argv[]) {
	
	int numbers[64];
    int count = 0;
    
    printf("Enter nums: ");

	while (scanf("%d", &numbers[count]) == 1 && getchar() != '\n') {
        count++;
    }
	
	int res_sum = find_sum(numbers, count);	
	int res_max = find_max(numbers, count);
	int res_min = find_min(numbers, count);	
	int res_avr = find_avr(numbers, count);
	
	printf("Sum: %d\nMax: %d\nMin: %d\nAvr: %d", res_sum, res_max, res_min, res_avr);
	
	
	return 0;
}
