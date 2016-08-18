#include "minitalk.h"

void get_client_pid(int signo)
{
    if (signo == SIGUSR2)
        clientpid = (1 << currBit) | clientpid;
    currBit++;
}
