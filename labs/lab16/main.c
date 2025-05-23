#include <stdio.h>
#include <string.h>

// https://habr.com/ru/articles/276957/

typedef unsigned int		u32;
typedef unsigned long long	u64;

//u32 cnt_long(u32 n) {
//	u32 result = 0;
//	
//    while(n) {
//    	result++;
//    	n &= n-1;
//	}
//	
//	return result;
//}
//
//u64 cnt_double(u64 n) {
//	u64 result = 0;
//	
//    while(n) {
//    	result++;
//    	n &= n-1;
//	}
//	
//	return result;
//}

u32 cnt_long(u32 n) {
	
	u32 result = 0;
	
	while (n) {
    	result += n&1; // proverka mladshego bita, samiy praviy == 1
    	n >>= 1; // n = n >> 1 011100 000111
	}
	return result;
}

u64 cnt_double(u64 n) {
	
	u64 result = 0;
	
    while (n) {
    	result += n&1;
    	n >>= 1;
  	}
	return result;
}

int main() {
	
	long numl;
	double numd;
	
	printf("Enter long num: "); 
	scanf("%ld", &numl);
	printf("Bit count: %d\n", cnt_long(numl));

	
	printf("Enter double num: "); 
	scanf("%lf", &numd);
	printf("Bit count: %d\n", cnt_double(numd));

    return 0;
}
