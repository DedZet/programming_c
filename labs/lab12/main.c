#include "calendar.h"
#include <time.h>

int main(int argc, char *argv[]) {

	char input[12];
	printf("Enter date (yyyy.mm.dd): ");
	scanf("%s", input);
	
	char year[5], month[3], day[3];
	int len = strlen(input);
	int daycode, leapyear;
	
	if (len == 10) { // yyyy.mm.dd
	
		strncpy(year, input, 4); year[4] = '\0';
		strncpy(month, input+5, 2); month[2] = '\0';
		strncpy(day, input+8, 2);  day[2] = '\0';
		
		struct tm t;
		t.tm_year = atoi(year) - 1900;
		t.tm_mon = atoi(month) - 1;	
		t.tm_mday = atoi(day);
//		t.tm_hour = 0;
//		t.tm_min = 0;
//		t.tm_sec = 0;
//		t.tm_isdst = -1;
		mktime(&t);
		
		printf("The day of the week is %s", format(&t, "%A"));
		//printf("The day of the week is %s", dayname[t.tm_wday-1]);
	}
	
	else if (len == 7) { // yyyy.mm
	
		strncpy(year, input+2, 2); year[4] = '\0';
		strncpy(month, input+5, 2); month[2] = '\0';
		
		struct tm t;
		t.tm_year = atoi(year) - 1900;
		t.tm_mon = atoi(month);
		
		mktime(&t);

		daycode = set_daycode(t.tm_year);
		is_leap(t.tm_year);
	
		print_month(t.tm_mon, daycode);
		printf("\n");
		
		daycode = set_daycode(t.tm_year);
	}
	
	else if (len == 4) { // yyyy
	
		strncpy(year, input+2, 2); year[4] = '\0';
		
		int inyear = atoi(year);
		int daycode = set_daycode(inyear);
		is_leap(inyear);
		
		print_calendar(daycode);
	}
	
	else if ((strcmp(input, "now")) == 0) {
		struct tm *local;
		time_t t = time(NULL);
		
		local = localtime(&t);
		printf("Current time: %s", asctime(local));
	}
	
	else printf("Unknown input");
	return 0;
}
