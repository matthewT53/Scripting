/*
	Name: Matthew Ta
	Date: 24/11/2015
	Description: Variable length argument lists
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <assert.h>

#define DEBUG // debugging constant

double average(int nitems, ...); // function that receives a variable # of args and returns the avg

int main(void)
{
	printf("Average is: %.2f\n", average(3, 5.0, 6.0, 7.0));
	return EXIT_SUCCESS;
}

double average(int nitems, ...)
{
	double total = 0;
	int j = 0;
	va_list ap; // type to hold the arguments

	#ifdef DEBUG
		printf("nitems: %d\n", nitems);
	#endif
	
	va_start(ap, nitems); // initialise the type that holds all the args
	for (j = 0; j < nitems; j++){
		// printf("%.2f\n", va_arg(ap, double));
		total += va_arg(ap, double); // get the next arg
	}

	#ifdef DEBUG
		printf("Total = %.2f\n", total);
	#endif
	va_end(ap);
	return (total / nitems);
}

