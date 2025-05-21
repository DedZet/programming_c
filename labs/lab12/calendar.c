#include <stdio.h>
#include <time.h>
#include <stdlib.h>

// https://iq.opengenus.org/calendar-application-in-c-programming/

int days_in_month[] = {0,31,28,31,30,31,30,31,31,30,31,30,31};

char *format(struct tm *p, char *format) {
	time_t t;
	char s[32];
	
	t = time(NULL);
	p = gmtime(&t);
	strftime(s, 32, format, p);

	return s;
}


char *months[]= {
	" ",
	"January",
	"February",
	"March",
	"April",
	"May",
	"June",
	"July",
	"August",
	"September",
	"October",
	"November",
	"December"
};

char *dayname[]= {
	"Monday",
	"Tuesday",
	"Wednesday",
	"Thursday",
	"Friday",
	"Saturday",
	"Sunday" 
};

int set_daycode(int year) {
	
	int daycode;
	int d1, d2, d3;
	
	d1 = (year - 1) / 4;
	d2 = (year - 1) / 100;
	d3 = (year - 1) / 400;
	
	daycode = (year + d1 - d2 + d3) % 7;
	return daycode;
}


int is_leap(int year) {
	if (year % 4 == 0 && year%100 != 0 || year%400 == 0) {
		days_in_month[2] = 29;
		return 1;
	}
	else {
		days_in_month[2] = 28;
		return 0;
	}
}

void print_calendar(stuct int year, int daycode) {
	
	int month, day;
	for ( month = 1; month <= 12; month++ )
	{
		printf("\n-------------%s-------------", months[month]);
		printf("\nSun  Mon  Tue  Wed  Thu  Fri  Sat\n" );

		for ( day = 1; day <= 1 + daycode * 5; day++ ) {
			printf(" ");
		}

		for ( day = 1; day <= days_in_month[month]; day++ ) {
			printf("%2d", day);
			if ( (day + daycode) % 7 > 0 ) printf("   " );
			else printf("\n " );
		}
		daycode = ( daycode + days_in_month[month] ) % 7;
	}
}

void print_month(int year, int mon, int daycode)
{
	int month, day;
	for (month = 1; month <= 12; month++ )
	{
			
		if (month == mon) {
			
			printf("\n-------------%s-------------", months[month]);
			printf("\nSun  Mon  Tue  Wed  Thu  Fri  Sat\n" );
		
			for ( day = 1; day <= 1 + daycode * 5; day++ ) {
				printf(" ");
			}
			
			for ( day = 1; day <= days_in_month[month]; day++) {
				printf("%2d", day);
			
			if ( ( day + daycode ) % 7 > 0 ) printf("   " );
			else printf("\n " );
			}
		break;
		}	
		
		daycode = ( daycode + days_in_month[month] ) % 7;
	}
}
