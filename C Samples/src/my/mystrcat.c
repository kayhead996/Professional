#include "my.h"

char *my_strcat(char *a, char *b)
{
    int i = 0, j = 0;
    if (a && b)
    {
        for (i = 0; a[i] != '\0'; i++)
            ;
        for (j = 0; b[j] != '\0'; j++)
            a[i++] = b[j];
        a[i] = '\0';
    }

    return a;
}
