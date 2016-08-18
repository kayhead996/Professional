#include "my.h"

int my_rfind(char *str, char letter)
{
    int index = -1, i = 0;
    if (str)
    {
        for (i = 0; str[i] != '\0'; i++)
            if (str[i] == letter)
                index = i;
        if (letter == '\0')
            index = i;
    }
    return index;
}
