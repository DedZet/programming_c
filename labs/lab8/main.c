#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <windows.h>


typedef struct {
	char name[32];
	char surname[32];
	int year;
	char gen;
	float height;
} Human;

int compare(Human a, Human b)
{
    return a.year - b.year;
}

int main(int argc, char *argv[]) {
	
	SetConsoleOutputCP(CP_UTF8);
	
	Human humans[4];
    Human sorted[4];
	
	FILE *names = fopen("names.txt","r");
	
	FILE *sorted_year = fopen("out_year.txt","w");
	FILE *sorted_names = fopen("out_names.txt","w");
	FILE *sorted_surnames = fopen("out_surnames.txt","w");
	FILE *sorted_gen = fopen("out_gen.txt","w");
	FILE *sorted_height = fopen("out_height.txt","w");
		
	if (names == NULL) {
		printf("File opening error");
		fclose(names);
	}
	
	int year;
	char line[256], name[32], surname[32];
	char gen;
	float height;
	
	while (fgets(line, sizeof(line), names)) {
	
        if (sscanf(line, "%s %s %d %c %f", name, surname, &year, &gen, &height) == 5) {
            printf("%s %s %d %c %f\n", name, surname, year, gen, height);
                
            int i, j;
    		for (i = 0; i < 4; i++) {
        		humans[i].name[32] = name;
				humans[i].surname[32] = surname;
				humans[i].year = year;
				humans[i].gen = gen;
				humans[i].height = height;
    
			} 
        }
    }        
    
    int i;
    for (i = 0; i < 6; i++) {
        printf("%s %s %d %c %f\n", humans[i].name, humans[i].surname, humans[i].year, humans[i].gen, humans[i].height);
    }
	
	
	
//	memcpy(sorted, humans, sizeof(humans));
//	
//    int humanbuff = sizeof(humans)/sizeof(humans[0]);
//    qsort(humans, humanbuff, sizeof(Human), compare);
	
	
	
	return 0;
}
