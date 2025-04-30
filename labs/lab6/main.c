#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <windows.h>


int main(int argc, char *argv[]) {
	
	FILE *namedb, *output;
	
	namedb = fopen("namedb.txt", "r");
	output = fopen("output.txt", "w");
	
	SetConsoleOutputCP(CP_UTF8);
	
	int year;
	char line[256], surname[50], name[50], surname2[50];
	
    while (fgets(line, sizeof(line), namedb))
    {
        if (sscanf(line, "%s %s %s %d", surname, name, surname2, &year) == 4) {
            if (year > 1980 && name[0] == 'À') {
                fprintf(output, "%s %s %s %d\n", surname, name, surname2, year);
                printf("%s %s %s %d\n", surname, name, surname2, year);
            }
        }
    }
	
	fclose(namedb);
	fclose(output);
	
	return 0;
}
