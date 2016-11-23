/*
    Name: Matthew Ta
    Date: 25/8/2015
    Description: Experiment with formatting in C
*/

#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    int x = 1987654;
    printf("%i\n", x);  
    printf("%o\n", x); // octal  
    printf("%u\n", x); // unsigned int
    printf("%x\n", x); // hex - lowercase
    printf("%X\n", x); // hex - uppercase

    printf("%lo\n", (long) x); // long octal
    printf("%ho\n", (short) x); // short octal 
    
    printf("%lx\n", (long) x); // long hex
    printf("%hx\n", (short) x); // short hex
    
    return EXIT_SUCCESS;
}
