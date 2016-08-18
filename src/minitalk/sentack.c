#include "minitalk.h"

void sent_ack(int signo)
{
    if (signo == SIGUSR1)
        gl_ack = 1;
}
