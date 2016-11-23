/*
    Name: Matthew Ta
    Date: 26/8/2015
    Description: Experiements with field widths and precisions
*/

#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    int x = 856;
    printf("%4d\n", x);
    printf("%5.4d\n", x);
    printf("%4.5d\n", x);

    float y = 1234.345645;
    printf("%9.3f\n", y);

    double z = 235.5345346;
    printf("%8.2f\n", z);

    return EXIT_SUCCESS;
}
