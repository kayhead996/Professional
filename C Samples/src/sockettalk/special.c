#include "sockettalk.h"

int special(char *buffer)
{
    int ret = 0;

    if (my_strcmp(buffer, "/exit") == 0 || my_strncmp(buffer, "/nick", 5) == 0 || my_strncmp(buffer, "/me", 3) == 0)
        ret = 1;

    return ret;
}
