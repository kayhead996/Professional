#include "minishell.h"

char *my_read()
{
    int i = 0;
    char *buffer = malloc(1024 * sizeof(char));
    char c = ' ';

    while (c != '\n')
    {
        read(0, &c, 1);
        buffer[i++] = c;
    }

    buffer[i] = '\0';

    return buffer;
}
