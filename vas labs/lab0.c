#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

void erat(int n) {

    bool *isPrime = (bool *)malloc((n + 1) * sizeof(bool)); // выделение памяти для bool списка
    for (int i = 0; i <= n; i++) {
        isPrime[i] = true; 
    } // заполнение списка

    for (int p = 2; p * p <= n; p++) {
        if (isPrime[p] == true) {
            for (int i = p * p; i <= n; i += p) {
                isPrime[i] = false;
            }
        }
    } // обработка простых чисел
    
    for (int p = 2; p <= n; p++) {
        if (isPrime[p]) {
            printf("%d ", p);
        } // вывод простых чисел
    }
    free(isPrime); // освобождение памяти
}

int main() {
    int n;
    printf("Введите целое неотрицательное n: ");
    scanf("%d", &n);
    printf("\n");
    erat(n);
    
    return 0;
}
