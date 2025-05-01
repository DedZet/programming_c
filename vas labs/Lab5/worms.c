#include <stdio.h>

int main() {
	
    int N, L;
    
    printf("Enter input:\n");
    scanf("%d %d", &N, &L);
    
    int A[N-1], B[N-1];
    
    int i;
    for (i = 0; i < N-1; i++) {
        scanf("%d", &A[i]);
    }
    for (i = 0; i < N-1; i++) {
        scanf("%d", &B[i]);
    }
    
    int result = 0;
    for (i = 0; i < N-1; i++) {
        result += B[i] / L;
    }
    
    printf("Result: %d\n", result);
    return 0;
}
