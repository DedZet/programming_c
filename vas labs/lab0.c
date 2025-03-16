#include <stdio.h>

int main() {
    
    int P[] = {1,2,3,4,5,6};
    int p = 2;
    
    for (int i = 0; i < sizeof(P); i++) {
        if ((P[i] % p) == 0) {
            printf("\n%i", P[i]);
        }
    }
    
    return 0;
}
