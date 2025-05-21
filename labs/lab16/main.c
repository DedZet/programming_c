#include <stdio.h>
#include <stdint.h>

int cnt_long(long num) {
	
    int count = 0;
    unsigned long unum = (unsigned long)num;
    
    while (unum != 0) {
        count += unum & 1; 
        unum >>= 1;
    }
    return count;
}

int cnt_double(double num) {
    int count = 0;
    uint64_t *ptr = (uint64_t *)&num;
    uint64_t bits = *ptr;
    
    int i;
    for (i = 0; i < 64; i++) {
        count += (bits >> i) & 1;
    }
    return count;
}

int main() {
	
    long numL;
    double numD;

    printf("Enter long: ");
    scanf("%ld", &numL);
    printf("Bit count: %d\n", cnt_long(numL));

    printf("\nEnter double: ");
    scanf("%lf", &numD);
    printf("Bit count: %d\n", cnt_double(numD));

    return 0;
}
