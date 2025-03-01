#include <stdio.h>
int main() {
    char text[16];
    
    scanf("%s", &text);
    
    char mod[16];
    char ch;
    
    int i = 0;
    while (text[i]) {
        ch = text[i];
        putchar(toupper(ch));
        i++;
    }
    return 0;
}
