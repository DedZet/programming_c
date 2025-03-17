#include <stdio.h>
#include <stdbool.h>
#include <math.h>

void endl() {
    printf("\n");
}

void printarr(int arr[]) {
    int len = sizeof(arr) - 1;
    for (int i = 0; i < len; i++) {
        printf("%d ",arr[i]);
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

int* makearr(int n) {
    
    static int arr[32];
    
    for (int i = 0; i < n + 1; i++) {
        arr[i] = i;
    }
    
    return arr;
}

int main() {
    
    int P[] = {1,2,4,3,5,6,7,11,12,13,20};
    int p = 2;
    
    int* jojo = makearr(22);
    
    //printarr(P);
    //endl();
    printarr(jojo);
    
    int len = sizeof(P) / sizeof(P[0]);

    for (int i = 0; i < len; i++) {
        if (!isprime(P[i])) {
            P[i] = 0;
        }
    }
    
    // endl();
    // printarr(P);
    
        while (p < len) {
        for (int co = 0; co < len; co++) {
            if (co != 0 && p < P[co] ) {
                p = P[co];
                break;
            }
        }
        }
        
    // endl();
    // printf("%i", p);
    
    return 0;
}
