#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "calendar.h"

char *cast_wday(int wday) {
	switch (wday+1) {
		case 1:
			return "Monday";
			break;
		case 2:
			return "Tuesday";
			break;
		case 3:
			return "Wednesday";
			break;
		case 4:
			return "Thursday";
			break;
		case 5:
			return "Friday";
			break;
		case 6:
			return "Saturday";
			break;
		case 7:
			return "Sunday";
			break;
	}
}

char* cast_month(int month) {
	switch (month-1) {
		case 0:
			return "January";
			break;
		case 1:
			return "February";
			break;
		case 2:
			return "March";
			break;
		case 3:
			return "April";
			break;
		case 4:
			return "May";
			break;
		case 5:
			return "June";
			break;
		case 6:
			return "July";
			break;
		case 7:
			return "August";
			break;
		case 8:
			return "September";
			break;
		case 9:
			return "October";
			break;
		case 10:
			return "November";
			break;
		case 11:
			return "December";
			break;	
	}
}

int is_leap(int year) {
	if (year % 400 == 0 || (year % 4 == 0 && year % 100 != 0)) return 1;
	else return 0;
}

int get_days(int month, int year) {
	int days[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
	
	if (is_leap(year) && (month == 2)) return 29;
	else return days[month-1];
}

void print_mon_calendar(int month, int year) {
	printf("\n--------- %s ---------\n", cast_month(month));
	printf("Mo  Tu  We  Th  Fr  Sa  Su\n");
	int days = get_days(month, year);
	
	int d;
	for (d = 1; d <= days; d++) {
		printf("%d  ", d);
		
		if ((d + days) % 7 == 0) {
			printf("\n");
		}
	}
}


int main(int argc, char *argv[]) {

	char input[12];
	
	printf("Enter date (yyyy.mm.dd): ");
	scanf("%s", input);
	
	char year[5], month[3], day[3];
	int len = strlen(input);
	
	if (len == 10) { // yyyy.mm.dd
		strncpy(year, input, 4); year[4] = '\0';
		strncpy(month, input+5, 2); month[2] = '\0';
		strncpy(day, input+8, 2);  day[2] = '\0';
		
		struct tm t;
		t.tm_year = atoi(year) - 1900;
		t.tm_mon = atoi(month) - 1;
		t.tm_mday = atoi(day);
		
		mktime(&t);
		printf("The day of the week is %s", cast_wday(t.tm_wday));
	}
	
	else if (len == 7) { // yyyy.mm
		strncpy(year, input+2, 2); year[4] = '\0';
		strncpy(month, input+5, 2); month[2] = '\0';
		
//		printf("Calendar of the month:\n");
//		print_mon_calendar(atoi(month), atoi(year));

int inyear, daycode, leapyear;

	if(argc > 1)
		inyear = atoi(argv[1]);	
	else
		inyear = atoi(year);	

	daycode = determinedaycode(inyear);
	determineleapyear(inyear);
	
	print_month(inyear, atoi(month), daycode);
	printf("\n");
		
	daycode = determinedaycode(atoi(year));
		
	}
	
	else if (len == 4) { // yyyy
		strncpy(year, input+2, 2); year[4] = '\0';
		
//		printf("Calendar of the year:\n");
//		print_year_calendar(atoi(year), daycode(atoi(year)));
		
		int inyear, daycode, leapyear;

	if(argc > 1)
		inyear = atoi(argv[1]);	
	else
		inyear = atoi(year);

	daycode = determinedaycode(inyear);
	determineleapyear(inyear);
	calendar(inyear, daycode);
	printf("\n");
		
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
	return 0;
}
