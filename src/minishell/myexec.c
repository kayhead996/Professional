#include "minishell.h"

void my_exec(char **commandVect)
{
    int status = 0;
    pid_t pid;

    if (commandVect[0])
    {
        if ((pid = fork()) == 0)
        {
            status = execvp(commandVect[0], commandVect);
            my_int(status);
            my_str("\n");
            if (status < 0)
            {
                if (commandVect[0])
                {
                    my_str("Cannot access ");
                    my_str(commandVect[0]);
                    my_str(". No file or directory found.\n");
                }

            }
            _exit(status);
        }
        else if (pid > 0)
            wait(&status);
        else
            my_str("fork() error.\n");
    }
    else
        status = -1;



}
