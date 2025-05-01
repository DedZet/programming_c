#include <stdio.h>

int find_max_div(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

int main() {
	
	int N, M;
	
	printf("Enter input:\n");
    scanf("%d %d", &N, &M);
    
    int num = N * M;
    int denum = M - N;

    int div = find_max_div(num, denum);
    
    num /= div;
    denum /= div;
    
    printf("Result: %d/%d\n", num, denum);
    return 0;
}
