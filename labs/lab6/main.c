#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <windows.h>


int main(int argc, char *argv[]) {
	
	FILE *namedb;
	FILE *output;
	
	namedb = fopen("namedb.txt", "r");
	output = fopen("output.txt", "w");
	int ch;
	SetConsoleOutputCP(CP_UTF8);
	
	int year;
	
	char line[128];
    while (fgets(line, sizeof(line), namedb)) 
	{
    	int i;
        for (i = 0; i < strlen(line) - 3; ++i) 
		{
            if (isdigit(line[i]) && isdigit(line[i+1]) && isdigit(line[i+2]) && isdigit(line[i+3])) 
			{		
					year = atoi(&line[i]);
					if (year > 1980) {
						printf("%d\n", year);
						fprintf(output, "%.4s\n", &line[i]);
					}
            }
        }
    }
	
	fclose(namedb);
	fclose(output);
	
	return 0;
}
