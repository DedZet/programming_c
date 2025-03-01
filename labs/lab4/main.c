#include <stdio.h>
#include <math.h>
#include <stdbool.h>

bool check(int a, int b, int c) {
    if (((a+b)>c) && ((a+c)>b) && ((b+c)>a)) {
        return true;
    }
    else {
        return false;
        }
    }

void get_perim(int a, int b, int c) {
    printf("P: %i", a+b+c);
}

void get_sq(int a, int b, int c) {
    int p = (a+b+c)/2;
    int s = sqrt(p*(p-a)*(p-b)*(p-c));
    printf("S: %i", s);
}

int main() {
    
    int a,b,c;
    printf("Enter nums\n");
    scanf("%i %i %i", &a, &b, &c);
    if (check(a,b,c)) {
        get_perim(a,b,c);
        get_sq(a,b,c);
    }
    
    return 0;
}
