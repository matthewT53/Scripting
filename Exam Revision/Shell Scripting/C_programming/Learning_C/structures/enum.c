#include <stdio.h>
#include <stdlib.h>

#define MONTHS 12

enum months{
    JAN = 1, FEB, MAR, APR, MAY, JUN, JUL, AUG, SEP, OCT, NOV, DEC // setting one of the middle values causes the for loop to stop mid way
};

int main(void)
{
    const char *monthsStr[MONTHS] = {"JANUARY", "FEBRUARY", "MARCH", "APRIL", "MAY", "JUNE",
                             "JULY", "AUGUST", "SEPTEMBER", "OCTOBER", "NOVEMBER", "DECEMBER"};
    enum months currMonth;
    
    for (currMonth = JAN; currMonth <= DEC; currMonth++){
        printf("%02d: %15s\n", currMonth, monthsStr[currMonth - 1]); 
    }

    return EXIT_SUCCESS;
}
