#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main()
{

    char *s = "Hello World";
    while (*s)
    {
        printf("%c", *s++);
    }
    return 0;
}