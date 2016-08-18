#include "my.h"
#include <stdio.h>

int my_revstr(char *str)
{
    char tmp = ' ';
    int length = -1, start = 0, end = 0;
    if (str)
    {
        length = my_strlen(str);
        if (length > 1)
        {
            for (start = 0, end = length - 1; start < end; start++, end--)
            {
                tmp = str[start];
                str[start] = str[end];
                str[end] = tmp;
            }
            str[length] = '\0';
        }
    }
    return length;
}
