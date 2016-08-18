#include "my.h"

char *my_strdup(char *a)
{
    int size = 0;
    char *ret = NULL;

    if (a)
    {
        for (size = 0; a[size] != '\0'; size++)
            ;

        ret = (char *)malloc(size * sizeof(char));

        for (size = 0; a[size] != '\0'; size++)
            ret[size] = a[size];

        ret[size] = '\0';
    }

    return ret;
}
