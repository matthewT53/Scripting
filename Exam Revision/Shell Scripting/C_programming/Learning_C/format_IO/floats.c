/*
    Name: Matthew Ta
    Date: 25/8/2015
    Description: Experimenting with floats
*/

#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    double x = 524762356564234.34697963467;

    printf("x = %.8f\n", x); // float %f
    printf("x = %g\n", x); // %g
    printf("x = %G\n", x); // %G
    printf("x = %e\n", x); // e
    printf("x = %E\n", x); // E

    double y = 0.00000000005345346457;
    printf("\n");
    printf("y = %.20f\n", y); // float %f
    printf("y = %g\n", y); // %g
    printf("y = %G\n", y); // %G
    printf("y = %e\n", y); // e
    printf("y = %E\n", y); // E

    return EXIT_SUCCESS;
}
