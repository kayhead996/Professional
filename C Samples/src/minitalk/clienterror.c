#include "minishell.h"

void client_error(int signo)
{
    if (signo == SIGALRM)
        my_str("\nError connecting to the server, please check the PID passed.\n");
    _exit(0);
}
