#include "my.h"

char *my_strrindex(char *a, char b)
{
    int i = 0;
    char *ret = NULL;

    if (a)
        for (i = 0; a[i] != '\0'; i++)
            if (a[i] == b)
                ret = &a[i];

    return ret;
}
