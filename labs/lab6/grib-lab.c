#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <windows.h>
#include <wchar.h>

int isa(const char *str) {
	return (strlen(str) >= 2 && (unsigned char) str[0] == 0xD0 && (unsigned char) str[1] == 0x90);
}

int main(int argc, char *argv[]) {
	
	//setlocale(LC_ALL, "");
	
	FILE *namedb = fopen("namedb.txt", "r");
	FILE *output = fopen("output.txt", "w");
	
	SetConsoleOutputCP(CP_UTF8);
	setlocale(LC_ALL, "UTF-8");

	int year;
	char line[256], name[50], surname[50], surname2[50];
	
    while (fgets(line, sizeof(line), namedb))
    {
        if (sscanf(line, "%s %s %s %d", surname, name, surname2, &year) == 4) {
            //if (year > 1980) {
            if (strncmp(surname, "À", 2) == 0) {
                fprintf(output, "%s %s %s %d\n", surname, name, surname2, year);
                printf("%s %s %s %d\n", surname, name, surname2, year);
            }
        }
    }
	
	fclose(namedb);
	fclose(output);
	
	return 0;
}
