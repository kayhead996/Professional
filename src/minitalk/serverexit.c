#include "minitalk.h"

void server_exit(int signo)
{
    if (signo == SIGINT)
    {
        my_str("\nReceived SIGINT, quitting the server\n");
        _exit(0);
    }
}
