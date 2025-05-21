#include <stdio.h>
#include <string.h>

// https://habr.com/ru/articles/276957/

typedef unsigned int       u32;
typedef unsigned long long u64;

u32 cnt_long(u32 n) {
	u32 result = 0;
    while(n) {
    	result++;
    	n &= n-1;
	}
	
	return result;
}

u64 cnt_double(u64 n) {
	u64 result = 0;
    while(n) {
    	result++;
    	n &= n-1;
	}
	
	return result;
}

int main() {
	
	long numl;
	double numd;
	
	printf("Enter long num: "); 
	scanf("%ld", &numl);
	printf("Num has %d bytes\n", cnt_long(numl));
	    
	
	printf("Type double num: "); 
	scanf("%lf", &numd);
	printf("Numr has %d bytes\n", cnt_double(numd));

    return 0;
}
