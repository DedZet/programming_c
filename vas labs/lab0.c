#include <stdio.h>
#include <stdbool.h>
#include <math.h>

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
    
    int len = sizeof(P) / sizeof(P[0]);
    
    if (isprime(4)) {
        printf("True");
    }
    else {printf("False");}

    // for (int i = 0; i < len; i++) {
    //     if (isprime(P[i])) {
    //         printf("\n%i", P[i], "\n");
    //     }
    // }
    
    return 0;
}
