#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
	
	int sign(char* str, int i) {
		
		if (i < 0 || i >= strlen(str)) return 1;
		if (str[i] == '-') return -1;
    	else return 1;

	}
	
	//char exp[64];
	double result = 0.0;
	
	//printf("Enter expression: ");
	//scanf("%s", exp);
	
	//char* ops = strtok(exestr, "0123456789.");
	
	char exestr[64] = "-120+20+60-212+26";
    char* exp = strtok(exestr, "+"); 
    
	int i = 0;
    while (exp != NULL) {
    	
        	double num = strtod(exp, NULL); 
        	
        	printf("%.2lf\n", sign(exestr,i)*num); // 60-212
        	exp = strtok(NULL, "+-");
        	i++;
        }
        
        return 0;
    }	
