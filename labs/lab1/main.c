#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(int argc, char *argv[]) {
	float a, b, c, dm, x1, x2, d;
	
	a = 1;
	b = 5;
	c = 3;
	
	d = pow(b,2)-4*a*c; // pow - ñòåïåíü
	
	x1 = -b + sqrt(d)/(2*a);
	x1 = -b - sqrt(d)/(2*a);

	printf("D = %lf\n", d);
	printf("x1 = %lf\n", x1);
	printf("x2 = %lf\n", x2);
	
	return 0;
}
