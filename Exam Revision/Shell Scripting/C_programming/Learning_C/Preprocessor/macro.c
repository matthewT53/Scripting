/*
	Name: Matthew Ta
	Date: 6/10/2015
	Description: Experiment with macros
*/

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define DEBUG 0
#define NDEBUG // doesnt work
// #line 5


#define MY_ASSERT(x) ( (!x) ? abort() : x) // my assert function
#define HALF 0.5
#define AREA_TRIANGLE(L, B) ( (HALF) * (L) * (B) ) // macro to calculate the area of a triangle
#define AREA_WOMBAT(x, y, z) ( (x) * (x) \
+ (y) * (y) + (z) * (z) ) // multi line macro



int main(void)
{
	float area = 0;
	area = AREA_TRIANGLE(5, 2);
	printf("area = %.2f.\n", area);
	area = AREA_WOMBAT(2, 3, 5);
	printf("area of a wombat = %.2f\n", area);

	#ifdef DEBUG
		printf("Hello world.\n");
	#endif

	// predefined constants	
	printf("Time: %s\nDate: %s\n", __TIME__, __DATE__);
	printf("Line: %d.\n", __LINE__);
	printf("Name of source file: %s\n", __FILE__);

	int x = 5;
	int b = MY_ASSERT(x > 100);
	return EXIT_SUCCESS;
}
