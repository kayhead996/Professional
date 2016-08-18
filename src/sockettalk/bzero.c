#include "sockettalk.h"

void bzero(char *buffer, size_t buff_size)
{
    int i = 0;

    if (buffer)
        for (i = 0; i < (int)buff_size; i++)
            if (buffer[i])
                buffer[i] = '\0';
}
