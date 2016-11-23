/*
    Name: Matthew Ta
    Date: 26/8/2015
    Description: Playing with random format specs
*/

#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    int x = 0;
    int *xPtr = NULL;

    xPtr = &x;
    printf("x = %p\n", xPtr);
    printf("fsdfsdfsd fsdg %n\n", xPtr);
    printf("chars %% read: %d\n", *xPtr);

    return EXIT_SUCCESS;
}
