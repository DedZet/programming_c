#include <stdio.h>
#include <stdlib.h>

struct Human {
	char name[16];
	char surname[16];
	int year;
};

int main(int argc, char *argv[]) {
	
	struct Human humans[4];
	struct Human sorted[4];
	
	strcpy(humans[0].name, "Pavel");
	strcpy(humans[0].surname, "Ivlev");
	humans[0].year = 1984;
	
	strcpy(humans[1].name, "Pavel");
	strcpy(humans[1].surname, "Ivlev");
	humans[1].year = 1980;
	
	strcpy(humans[2].name, "Pavel");
	strcpy(humans[2].surname, "Ivlev");
	humans[2].year = 1990;
	
	strcpy(humans[3].name, "Pavel");
	strcpy(humans[3].surname, "Ivlev");
	humans[3].year = 1996;
	
	int i;
	for (i = 0; i < 4; i++) {
		printf("%d\n", humans[i].year);
	}
	
	
	
	//printf("%d", sorted);
	
	return 0;
}
