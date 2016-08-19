#include "my.h"

int my_maxstrlen(char **vect, int start, int end)
{
    int i, max = 0;

    for (i = start; i < end && vect[i]; i++)
        if (my_strlen(vect[i]) > max)
            max = my_strlen(vect[i]);

    return max;

}
