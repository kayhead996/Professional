#include "my.h"

char *my_vect2str(char **x)
{
    int size = 0, i = 0, j = 0;
    char *str = NULL;

    if (x)
    {
        for (i = 0; x[i]; i++)
            for (j = 0; *(*(x + i) + j) != '\0'; j++)
                size++;

        str = (char *)malloc(size * sizeof(char));

        for (size = 0, i = 0; x[i]; i++)
        {
            for (j = 0; *(*(x + i) + j) != '\0'; j++)
                str[size++] = *(*(x + i) + j);
            str[size++] = ' ';
        }

        str[size] = '\0';
    }

    return str;
}
