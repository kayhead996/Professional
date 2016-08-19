#include "sockettalk.h"

void bcopy(char *src, char *dst, size_t buff_size)
{
    int i = 0;

    for (i = 0; i < (int)buff_size; i++)
        dst[i] = src[i];
}
