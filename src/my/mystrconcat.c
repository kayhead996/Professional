#include "my.h"

char *my_strconcat(char *a, char *b)
{
    int size = 0, i = 0;
    char *ret = NULL;

    if (a && b)
    {
        for (i = 0; a[i] != '\0'; i++, size++)
            ;

        for (i = 0; b[i] != '\0'; i++, size++)
            ;

        --size;

        ret = (char*)malloc(size * sizeof(char));

        for (i = 0; a[i] != '\0'; i++)
            ret[i] = a[i];

        for (size = 0; b[size] != '\0'; size++, i++)
            ret[i] = b[size];

        ret[i] = '\0';
    }
    else if (a)
        ret = a;
    else if (b)
        ret = b;

    return ret;
}
