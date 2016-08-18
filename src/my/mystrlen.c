#include "my.h"

int my_strlen(char *str)
{
    int length = -1;

    if (str)
        for (length = 0; str[length] != '\0'; length++)
            ;

    return length;
}
