#include "my.h"

void my_str(char *str)
{
    if (str)
    {
        int i = 0;
        for (i = 0; str[i] != '\0'; i++)
            my_char(str[i]);
    }
}
