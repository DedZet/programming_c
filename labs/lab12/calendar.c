#include <stdio.h>
#include <time.h>

#define TRUE    1
#define FALSE   0
#define KGRN  "\x1B[32m"
#define RED   "\x1B[31m"
#define YEL   "\x1B[33m"
#define RESET "\x1B[0m"

int days_in_month[]={0,31,28,31,30,31,30,31,31,30,31,30,31};
int today_year = -1, today_month = -1, today_day = -1;

char *months[]=
{
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


int determinedaycode(int year)
{
	int daycode;
	int d1, d2, d3;
	
	d1 = (year - 1.)/ 4.0;
	d2 = (year - 1.)/ 100.;
	d3 = (year - 1.)/ 400.;
	daycode = (year + d1 - d2 + d3) %7;
	return daycode;
}


int determineleapyear(int year)
{
	if(year% 4 == FALSE && year%100 != FALSE || year%400 == FALSE)
	{
		days_in_month[2] = 29;
		return TRUE;
	}
	else
	{
		days_in_month[2] = 28;
		return FALSE;
	}
}

void calendar(int year, int daycode)
{
	int month, day;
	for ( month = 1; month <= 12; month++ )
	{
		printf("\n-------------%s-------------", months[month]);
		printf("\nSun  Mon  Tue  Wed  Thu  Fri  Sat\n" );
		
		// Correct the position for the first date
		for ( day = 1; day <= 1 + daycode * 5; day++ )
		{
			printf(" ");
		}
		
		// Print all the dates for one month
		for ( day = 1; day <= days_in_month[month]; day++ )
		{
				printf("%s%2d%s", YEL, day, RESET );
			
			// Is day before Sat? Else start next line Sun.
			if ( ( day + daycode ) % 7 > 0 )
				printf("   " );
			else
				printf("\n " );
		}
		// Set position for next month
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
		// Correct the position for the first date
		for ( day = 1; day <= 1 + daycode * 5; day++ )
		{
			printf(" ");
		}
			
		// Print all the dates for one month
		for ( day = 1; day <= days_in_month[month]; day++)
		{
				printf("%s%2d%s", YEL, day, RESET );
			
			// Is day before Sat? Else start next line Sun.
			if ( ( day + daycode ) % 7 > 0 )
				printf("   " );
			else
				printf("\n " );
		}
		break;
	}
		// Set position for next month
		daycode = ( daycode + days_in_month[month] ) % 7;

	}
}

