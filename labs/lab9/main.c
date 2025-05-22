#include <stdio.h>
#include <stdlib.h>
#include <string.h>

double eval(char *exp) {
	
    double result = 0;
    int sign = 1;
    char *token = strtok(exp, " "); // "5", "+", "3", "-", "2"
    
    while (token != NULL) {
        if (strcmp(token, "+") == 0) {
            sign = 1;
        }
        
        else if (strcmp(token, "-") == 0) {
            sign = -1;
        }
        
        else {
            double num = atof(token); // to double
            result += sign * num;
            //sign = 1;
        }
        
        token = strtok(NULL, " ");
    }
    
    return result;
}

int main() {
	
    char input[128];
    printf("Enter expression: ");
    
	fgets(input, sizeof(input), stdin); // read whole line
    
    double result = eval(input);
    printf("Result: %.2lf\n", result);
    
    return 0;
}
