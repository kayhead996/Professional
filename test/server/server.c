#include "minitalk.h"

int main()
{
    int i = 0;

    my_int(getpid());
    my_char('\n');

    signal(SIGINT, server_exit);

    while(1)
    {  
        currBit = 0;
        clientpid = 0;
        currChar = (char)0;

        signal(SIGUSR1, get_client_pid);
        signal(SIGUSR2, get_client_pid);

        for (i = 0; i < sizeof(pid_t) * 8; i++)
            pause();


        kill(clientpid, SIGUSR1);


        signal(SIGUSR1, get_client_char);
        signal(SIGUSR2, get_client_char);


        do
        {
            currChar = (char)0;
            currBit = 0;
            for (i = 0; i < sizeof(char) * 8; i++)
                pause();
            my_char(currChar);
        }
        while (currChar != '\0');

        my_char('\n');
    }

    return 0;
}
