#include <stdio.h>
#include <stdlib.h>

typedef struct _something{
    unsigned int x : 4;
    unsigned int : 0; // padding must be same type as element in same mem block
    unsigned int y : 2;

} something;

int main(void)
{
    something example = {15,3};
    printf("something.x = %u and something.y = %u\n", example.x, example.y);
    return EXIT_SUCCESS;
}
