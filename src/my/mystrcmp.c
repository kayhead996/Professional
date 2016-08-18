#include "my.h"

int my_strcmp(char *a, char *b)
{
    int i = 0, j = 0;
    int ret = 0;

    if (a && b)
    {
        for (i = 0; a[i] != '\0'; i++)
            ;

        for (j = 0; b[j] != '\0'; j++)
            ;

        if (i == 0)
        {
            if (j > 0)
                ret = -1;
        }
        else if (j == 0)
        {
            if (i > 0)
                ret = 1;
        }
        else
        {
            for (i = 0; a[i] != '\0' && b[i] != '\0'; i++)
                if (a[i] > b[i])
                {
                    ret = 1;
                    break;
                }
                else if (a[i] < b[i])
                {
                    ret = -1;
                    break;
                }
        }
    }
    else if (!a)
        ret = -1;
    else if (!b)
        ret = 1;

    return ret;
}
