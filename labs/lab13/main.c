#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

void handler(int sig) {
    switch (sig) {
        case SIGABRT: 
			printf("processing  SIGABRT");
			break;
        case SIGFPE:  
			printf("processing SIGFPE");
			break;
        case SIGILL: 
			printf("processing SIGILL");
			break;
        case SIGINT: 
			printf("processing SIGINT");
			break;
        case SIGSEGV: 
			printf("processing SIGSEGV");
			break;
        case SIGTERM: 
			printf("processing SIGTERM");
			break;
        default:
			printf("Unknown signal");
			break;
    }
}

void handlers() {
    signal(SIGABRT, handler);
    signal(SIGFPE,  handler);
    signal(SIGILL,  handler);
    signal(SIGINT,  handler);
    signal(SIGSEGV, handler);
    signal(SIGTERM, handler);
}

int main() {
    handlers();
    
    int choise;
    
    printf("Chose signal:\n1. SIGABRT\n2. SIGFPE\n3. SIGILL\n4. SIGINT\n5. SIGSEGV\n6. SIGTERM\n");
    
    scanf("%d", &choise);
    
    if (choise == 0) exit(0);
	else if (choise == 1) abort();
	
	else if (choise == 2) {
		int a = 10;
		int b = 0;
		int c = a / b;
		(void)c;
	}
	
	else if (choise == 3) raise(SIGILL);
	else if (choise == 4) raise(SIGINT);
	
	else if (choise == 5) {
		int *ptr = NULL;
        *ptr = 42;
        (void)ptr;
	}
	
	else if (choise == 6) raise(SIGTERM);

    return 0;
}
    
