#include "my.h"

char *my_strnconcat(char *a, char *b, int n)
{
    int i = 0, size = 0;
    char *ret = NULL;

    if (a || b)
    {
        if (a)
            for (i = 0; i < n && a[i] != '\0'; i++, size++)
                ;
        if (b)
            for (i = 0; i < n && b[i] != '\0'; i++, size++)
                ;

        if (a && b)
            size--;

        ret = (char *)malloc(size * sizeof(char));
        i = 0;
        if (a)
            for (i = 0; i < n && a[i] != '\0'; i++)
                ret[i] = a[i];
        if (b)
            for (size = 0; size < n && b[size] != '\0'; i++, size++)
                ret[i] = b[size];

        if (n > 0)
            ret[i] = '\0';
    }

    return ret;
}
