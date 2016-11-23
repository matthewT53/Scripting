/*
    Name: Matthew Ta
    Date: 29/8/2015
    Description: Experimenting with scaf() function
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define STR_SIZE 150

int main(void)
{
    char str[STR_SIZE];
    int day, month, year;

    memset(str, 0, STR_SIZE);

    printf("Enter some letters: \n");
    scanf("%[azxcb]", str);
    printf("You entered: %s\n", str);
    memset(str, 0, STR_SIZE);
    printf("Enter some letters:");
    scanf("%[^zxcvb]", str);
    printf("You entered: %s\n", str);
    
    printf("Enter a date: (dd-mm-yy)\n");
    scanf("%d-%d-%d", &day, &month, &year);
    printf("Day: %d, month: %d and year: %d\n", day, month, year);

    return EXIT_SUCCESS;
}
