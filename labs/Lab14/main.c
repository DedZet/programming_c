#include <stdio.h>
#include <setjmp.h>

jmp_buf env; // buffer for saving the state

void fibonaci(int n, int *sum, int curr, int next) {
    if (n <= 0) {
        longjmp(env, 1); 
    }

    *sum += curr;
    printf("%d\n", curr);
    fibonaci(n - 1, sum, next, curr + next);
}

int main() {
	
    int count;
    printf("Enter count: ");
    scanf("%d", &count);

    int result = 0;

    if (setjmp(env) == 0) { // tochka returna
        fibonaci(count, &result, 1, 1);
    } else {
        printf("Result: %d\n", result);
    }

    return 0;
}
