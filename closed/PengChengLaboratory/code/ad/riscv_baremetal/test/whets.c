#include <stdio.h>
#include <stdint.h>
#include <math.h>

void pa(float e[4], float t, float t2)
{
	long j;
	for (j = 0; j < 6; j++)
	{
		e[0] = (e[0] + e[1] + e[2] - e[3]) * t;
		e[1] = (e[0] + e[1] - e[2] + e[3]) * t;
		e[2] = (e[0] - e[1] + e[2] + e[3]) * t;
		e[3] = (-e[0] + e[1] + e[2] + e[3]) / t2;
	}
}

void p3(float *x, float *y, float *z, float t, float t1, float t2)
{
	*x = *y;
	*y = *z;
	*x = t * (*x + *y);
	*y = t1 * (*x + *y);
	*z = (*x + *y) / t2;
}

void whet(void)
{
	long n1,n2,n5,n6,n8,n1mult;
	float e1[4], x, y, z;
	int i;

	float t  = 0.49999975;
	float t1 = 0.50000025;
	float t2 = 2.0;

	n1 = 12*100;
	n2 = 14*100;
	n5 = 32*100;
	n6 = 899*100;
	n8 = 93*100;
	n1mult = 10;

	printf("Start mini-whetstone.\n");

	/* Section 1, Array elements (Floating Point) */
	e1[0] = 1.0;
	e1[1] = -1.0;
	e1[2] = -1.0;
	e1[3] = -1.0;
	for (i = 0; i < n1*n1mult; i++) {
		e1[0] = (e1[0] + e1[1] + e1[2] - e1[3]) * t;
		e1[1] = (e1[0] + e1[1] - e1[2] + e1[3]) * t;
		e1[2] = (e1[0] - e1[1] + e1[2] + e1[3]) * t;
		e1[3] = (-e1[0] + e1[1] + e1[2] + e1[3]) * t;
	}
	printf("  N1 (bf8ff7d0): %.8lx\n", *(uint32_t*)&e1[3]);

	/* Section 2, Array as parameter (Floating Point) */
	for (i = 0; i < n2; i++)
		pa(e1, t, t2);
	printf("  N2 (bf8fb630): %.8lx\n", *(uint32_t*)&e1[3]);

	/* Section 5, Trig functions */
	x = 0.5;
	y = 0.5;
	for (i = 1; i < n5; i++) {
		x = t*atan(t2*sin(x)*cos(x)/(cos(x+y)+cos(x-y)-1.0));
		y = t*atan(t2*sin(y)*cos(y)/(cos(x+y)+cos(x-y)-1.0));
	}
	printf("  N5 (3eff8b5c): %.8lx\n", *(uint32_t*)&y);

	/* Section 6, Procedure calls (Floating Point) */
	x = 1.0;
	y = 1.0;
	z = 1.0;
	for (i = 0; i < n6; i++)
		p3(&x, &y, &z, t, t1, t2);
	printf("  N6 (3f7ffffd): %.8lx\n", *(uint32_t*)&z);

	/* Section 8, Standard functions (exp, sqrt, log) */
	x = 0.75;
	for (i = 0; i < n8; i++)
		x = sqrt(exp(log(x)/t1));
	printf("  N8 (3f4048a8): %.8lx\n", *(uint32_t*)&x);

	printf("Finish mini-whetstone.\n");
}
