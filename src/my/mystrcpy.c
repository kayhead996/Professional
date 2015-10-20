#include "my.h"

char *my_strcpy(char *a, char *b)
{
    int i = 0;

    if (a && b)
    {
        for (i = 0; b[i] != '\0'; i++)
            a[i] = b[i];
        a[i] = '\0';
    }

    return a;
}
