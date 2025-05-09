#include <stdio.h>
#include <ctype.h>

int main() {
	
    char exp[256];
    
    printf("Enter expression: ");
    scanf("%256s", exp);
    
    double result = 0;
    double num = 0;
    char op = '+';

	int i = 0;
    while (exp[i] != '\0' && exp[i] != '\n') {
        while (exp[i] == ' ') i++; // string skip 
        
        if (isdigit(exp[i]) || exp[i] == '.') {
            double temp = 0;
            int dot = 0;
            double div = 1;
            
            while (isdigit(exp[i]) || exp[i] == '.') {
                if (exp[i] == '.') {
                	if (dot) {
						printf("NaN\n");
                		return 1;
                	}
                
                dot = 1;
            	}
                
				else {
                    if (dot) {
                        div *= 10;
                        temp = temp * 10 + (exp[i] - '0');
                    }
					else {
                        temp = temp * 10 + (exp[i] - '0');
                    }
                }
                i++;
            }
            
            if (dot) temp /= div;
            num = temp;
        }
        

        if (exp[i] == '+' || exp[i] == '-' || exp[i] == '\0') {
            if (op == '+') result += num;
            else if (op == '-') result -= num;
             
            if (exp[i] != '\0') {
                op = exp[i];
                i++;
            }
            num = 0;

    	}
	}
    
    printf("Result: %.2lf\n", result);
    return 0;
}
