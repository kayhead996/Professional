#include "sockettalk.h"

void error(const char *msg)
{
    perror(msg);
    _exit(0);
}
