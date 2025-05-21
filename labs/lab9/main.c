#include <stdio.h>
#include <stdlib.h>
#include <string.h>

double eval(char *exp) {
	
	double result = 0;
    int sign = 1;
    
    while (*exp != "\0") {
        if (*exp == ' ') {
			exp++;
			continue;
		}
        
        if (*exp == '+') {
            sign = 1;
            exp++;
        }
        
        else if (*exp == '-') {
            sign = -1;
            exp++;
        }
        
        char *end;
        double num = strtod(exp, &end);
        
        if (exp == end) {
        	break;
		}
        
        result += sign * num;
        exp = end;
        sign = 1;  
    }
    return result;
}

int main() {
	
    char input[128];
    printf("Enter expression: ");
    scanf("%s", input);
    
    double result = eval(input);
    printf("Result: %.2lf\n", result);
    
    return 0;
}
