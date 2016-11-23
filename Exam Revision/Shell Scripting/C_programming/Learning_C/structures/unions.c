#include <stdio.h>
#include <stdlib.h>

union number{
    int x;
    double y;
};

int main(void)
{
    union number myNum;
    union number *numPtr = NULL;

    printf("sizeof(number) = %lu.\n", sizeof(myNum));
    myNum.x = 100;
    printf("myNum.x = %d and myNum.y = %g\n", myNum.x, myNum.y);
    myNum.y = 105.547457;
    printf("myNum.x = %d and myNum.y = %g\n", myNum.x, myNum.y);
    
    numPtr = &myNum;
    printf("myNum->x = %d and myNum->y = %g\n", numPtr->x, numPtr->y);
    numPtr->x = 5;
    printf("myNum->x = %d and myNum->y = %g\n", numPtr->x, numPtr->y);
    numPtr->y = 56.876;
    printf("myNum->x = %d and myNum->y = %g\n", numPtr->x, numPtr->y);
    numPtr->x = 9;
    printf("myNum->x = %d and myNum->y = %g\n", numPtr->x, numPtr->y);
    
    
    return EXIT_SUCCESS;
}
