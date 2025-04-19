#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <windows.h>

typedef struct {
	char name[32];
	char surname[32];
	int year;
	char sex;
	float height;
} Human;

int compare(Human a, Human b)
{
    return a.year - b.year;
}

int main(int argc, char *argv[]) {
	
	SetConsoleOutputCP(CP_UTF8);
	
	FILE *names = fopen("names.txt","r");
	
	FILE *sorted_year = fopen("out_year.txt","w");
	FILE *sorted_names = fopen("out_names.txt","w");
	FILE *sorted_surnames = fopen("out_surnames.txt","w");
	FILE *sorted_sex = fopen("out_sex.txt","w");
	FILE *sorted_height = fopen("out_height.txt","w");
		
	if (names == NULL) {
		printf("File opening error");
		fclose(names);
	}
	
	int year;
	char line[256], name[32], surname[32];
	char sex;
	float height;
	
	while (putchar(names) != EOF) {
	
            if (fscanf(names, "%s", name) == 1) {
                //fprintf(sorted_sex, "%s %s %d %c %lf", name, surname, year, sex, height);
                printf("%s", name);
                
                //printf("%s %s %d %c %lf\n", name, surname, year, sex, height);
        }
}
	
	//qsort();
	
	
	
	return 0;
}
