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
		t.tm_year = atoi(year) - 1900;		// 2025
		t.tm_mon = atoi(month) - 1;			// 05
		t.tm_mday = atoi(day);				// 21
		
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
		
		int inyear = atoi(year);	

		daycode = set_daycode(inyear);
		is_leap(inyear);
	
		print_month(inyear, atoi(month), daycode);
		printf("\n");
		
		daycode = set_daycode(atoi(year));
	}
	
	else if (len == 4) { // yyyy
	
		strncpy(year, input+2, 2); year[4] = '\0';
		
		int daycode, leapyear;
		int inyear = atoi(year);
		
		daycode = set_daycode(inyear);
		is_leap(inyear);
		print_calendar(inyear, daycode);
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
