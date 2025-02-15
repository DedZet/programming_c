#include <stdio.h>
#include <stdlib.h>
#include <math.h>


int main(int argc, char *argv[]) {
	double a, b, c, dm, x1, x2, d;
	
	printf("Enter A: ");
	scanf("%lf,", &a);
	
	printf("Enter B: ");
	scanf("%lf,", &b);
	
	printf("Enter C: ");
	scanf("%lf,", &c);

	d = pow(b,2)-4*a*c; // pow - ñòåïåíü
	
	printf("\n");
	
	if (d < 0) 
	{
		printf("D = %lf\n", d);
		printf("Kornei net"); 
	}
////////////////////////////////////////////////
	else if (d == 0) 
	{
		x1 = -b /(2*a);
		printf("D = %lf\n", d);
		printf("x1 = %lf\n", x1);
	}
////////////////////////////////////////////////
	else 
	{
	x1 = -b + sqrt(d)/(2*a);
	x1 = -b - sqrt(d)/(2*a);

	printf("D = %lf\n", d);
	printf("x1 = %lf\n", x1);
	printf("x2 = %lf\n", x2);
		
	}
	
	return 0;
}
