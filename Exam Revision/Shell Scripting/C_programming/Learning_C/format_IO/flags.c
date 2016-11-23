/*
    Name: Matthew Ta
    Date: 29/8/2015
    Description: Experiments with flags
*/

#include <stdio.h>
#include <stdlib.h>

void signFlags(void);
void spaceFlag(void);
void hashFlag(void);
void combFlags(void);

int main(void)
{
    printf("%10s%10d%10c%10f\n\n", "hello", 7, 'a', 1.23 );
    printf("%-10s%-10d%-10c%-10f\n", "hello", 7, 'a', 1.23 );
    signFlags();
    spaceFlag();
    hashFlag();
    combFlags();
    return EXIT_SUCCESS;
}

void signFlags(void)
{
    printf("Sign flags.\n");
    printf("%+d\n", 145);
    printf("%-d\n", -145);
}

void spaceFlag(void)
{   
    printf("Space flags.\n");
    printf("% d and \n%d\n", 145, -145);
}

void hashFlag(void)
{
    int value = 235;
    double d_value = 234;

    printf("Hash flags.\n");
    printf("%#o\n", value);
    printf("%#x\n", value);
    printf("%#X\n", value);
    printf("%g\n", d_value);
    printf("%#g\n", d_value);
}

void combFlags(void)
{
    int x = 125655;
    
    printf("Combination of flags.\n");
    printf("%+09d\n", x);
    printf("%09d\n", x);    
}
