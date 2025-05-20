#include <stdio.h>
#include <setjmp.h>

jmp_buf env; // буфер для хранения состояний

void fibonaci(int n, int *sum, int curr, int next) {
    if (n <= 0) {
        longjmp(env, 1); // возвращает управление где был вызван setjump
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

    if (setjmp(env) == 0) { // точка возврата
        fibonaci(count, &result, 1, 1);
    } else {
        printf("Result: %d\n", result);
    }

    return 0;
}
