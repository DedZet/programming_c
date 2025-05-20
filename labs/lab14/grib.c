#include <stdio.h>
#include <setjmp.h>
 
jmp_buf env;
 
void testFunction() {
    puts("in testFunction before longjmp");
    longjmp(env, 22);
    puts("this string is inv");
}
 
int main() {
    switch (setjmp(env)) {
    	case 0:
        	puts("processing code before longjmp.");
        	testFunction();
        case 22:
        	printf("LOL");
	}

    return 0;
}
