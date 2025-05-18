#include <stdio.h>

void forward(int n) {
	
    if (n < 10) {
        printf("%d ", n);
    } else {
        forward(n / 10);
        printf("%d ", n % 10);
    }
}

void reverse(int n) {
	
    if (n < 10) {
        printf("%d ", n);
    } else {
        printf("%d ", n % 10);
        reverse(n / 10);
    }
}

int main() {
	
    int num;
    printf("Enter num: ");
    scanf("%d", &num);
    
    printf("\nForward: ");
    forward(num);
    printf("\nReverse: ");
    reverse(num);
    
    return 0;
}
