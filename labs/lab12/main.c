#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char *argv[]) {
	
//	t.tm_year = 90;
//	t.tm_mon = 1;
//	t.tm_mday = 7;
	
	//mktime(&t);
	
	char input[12];
	
	printf("Enter date (yyyy.mm.dd): ");
	scanf("%s", input);
	
	char year[5], month[3], day[3];
	int len = strlen(input);
	
	if (len == 10) {
		printf("First format"); // yyyy.mm.dd
	}
	
	else if (len == 7) {
		printf("Second format"); // yyyy.mm
	}
	
	else if (len == 4) { // yyyy
		printf("Third format");
	}
	
	else if ((strcmp(input, "now")) == 0) {
		struct tm *local;
		time_t t = time(NULL);
		local = localtime(&t);
		
		printf("Current time: %s", asctime(local));
	}
	
	else {
		printf("Unknown input");
	}
	
//	strncpy(year, input, 4); year[4] = '\0';
//	strncpy(month, input+5, 2); month[2] = '\0';
//	strncpy(day, input+8, 2);  day[2] = '\0';
	
	//printf("Y: %s\nM: %s\nD: %s", year, month, day);
	return 0;
}
