#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

double eval(char *urav) {
	
    char *exp;
    double result = 0.0;
    double num;
    int negative = 0;
    char *endptr;

    exp = strtok(urav, " +-");
    
    if (exp[0] == '-') {
        negative = 1;
    }

    if (exp != NULL) {
    	
        num = strtod(exp, &endptr);
        if (negative) result *= -1;
		else  result = result;
		
    }

    while ((exp = strtok(NULL, " +-")) != NULL) {
    }

    result = 0.0;
    char *ptr = exp;
    int sign = 1;
    
    while (*ptr) {
        if (*ptr == ' ') {
            ptr++;
            continue;
        }
        
        if (*ptr == '+') {
            sign = 1;
            ptr++;
        } else if (*ptr == '-') {
            sign = -1;
            ptr++;
        }
        
        while (*ptr == ' ') ptr++;
        
        num = strtod(ptr, &endptr);
        if (ptr == endptr) {
            printf("Error nan\n");
            exit(1);
        }
        
        result += sign * num;
        ptr = endptr;
    }
    
    return result;
}

int main() {
    char expression[64];
    
    //printf("Enter expression: ");
    
    char* test = "120+30-20-5.5";
    
    double result = eval(test);
    printf("Result: %.2lf\n", result);
    
    return 0;
}
