#include <stdio.h>
#include <string.h>

#define MAXLINE 80

int main(int argc, char **argv) {
    char line[MAXLINE];
    int count = 0;

    while (fgets(line, MAXLINE, stdin) != NULL) {
        if (strstr(line,"COMP2041") == line)
            count++;
    }
    printf("There are %d students in COMP2041\n", count);
    return 0;
}
