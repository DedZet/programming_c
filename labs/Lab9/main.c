#include <stdio.h>
#include <stdlib.h>

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main(int argc, char *argv[]) {
	
	char exp[64];
	double result = 0.0;
	
	//printf("Enter expression: ");
	//scanf("%s", exp);
	
	//char* ops = strtok(exestr, "0123456789.");
	
	char exestr[64] = "-120+20+60-212+26";
	
	char* nums = strtok(exestr, "+");
	
	while (nums != NULL) {
		printf("%.2lf\n", strtod(nums, NULL));
		nums = strtok(NULL, "+");
	}
	
	return 0;	
}
