#include "my.h"

char *my_strncpy(char *a, char *b, int n)
{
    int i = 0;

    if (a && b)
    {
        for (i = 0; i < n && b[i] != '\0'; i++)
            a[i] = b[i];
        a[i] = '\0';
    }

    return a;
}
