#include <stdio.h>
#include <locale.h>

int main(int argc, char *argv[]) {
	
	FILE *namedb = fopen("namedb.txt", "r");
	FILE *output = fopen("output.txt", "w");
	
//	SetConsoleOutputCP(CP_UTF8);
//	setlocale( LC_CTYPE, "rus" );

	int year;
	char line[256], name[50], surname2[50], surname[50];

    while (fgets(line, sizeof(line), namedb))
    {
        if (sscanf(line, "%s %s %s %d", surname, name, surname2, &year) == 4) {
            if (name[0] == 'À') { // year > 1980
                fprintf(output, "%s %s %s %d\n", surname, name, surname2, year);
                printf("%s %s %s %d\n", surname, name, surname2, year);
            }
        }
    }
	
	fclose(namedb);
	fclose(output);
	
	return 0;
}

// chcp 65001
// x86_64-w64-mingw32-gcc -m64 -o output64.exe main.c
