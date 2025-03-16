#include <stdio.h>
#include <stdbool.h>
#include <math.h>

void printarr(int arr[]) {
    int len = sizeof(arr) - 1;
    for (int i = 0; i < len; i++) {
        printf("%i ",arr[i]);
    }
}

bool isprime(int n) {
    int flag = 0;
    
    if (n == 0 || n == 1) {
        flag = 1;
    }
    
    for (int i = 2; i <= n / 2; i++) {
        if ((n % i) == 0) {
            flag = 1;
            break;
        }
    }
    
    if (flag == 0) {
        return true;
    }
    
    else {return false;}
}


int main() {
    
    int P[] = {1,2,3,4,5,6,7};
    int p = 2;
    
    printarr(P);
    
    int len = sizeof(P) / sizeof(P[0]);

    for (int i = 0; i < len; i++) {
        if (!isprime(P[i])) {
            P[i] = 0;
        }
    }
    
    printf("\n");
    printarr(P);
    
    return 0;
}
