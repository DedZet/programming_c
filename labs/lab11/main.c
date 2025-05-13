#include "module.h"

int main(int argc, char *argv[]) {
	
	int count = 5;
	
	int res_sum = find_sum(count, 12, 10, 2, 5, 78);	
	int res_max = find_max(count, 12, 10, 2, 5, 78);
	int res_min = find_min(count, 12, 10, 2, 5, 78);	
	int res_avr = find_avr(count, 12, 10, 2, 5, 78);
	
	printf("Sum: %d\nMax: %d\nMin: %d\nAvr: %d", res_sum, res_max, res_min, res_avr);
	
	return 0;
}
