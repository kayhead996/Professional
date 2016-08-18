#include "minitalk.h"

void get_client_char(int signo)
{
    if (signo == SIGUSR2)
        currChar = ((char)1 << (char)currBit) | currChar;
    currBit++;
}
