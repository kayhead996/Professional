#include "minishell.h"

void my_cd(char *command)
{
    int status = 0;

    if (command)
    {
        if (my_strcmp(command, "~") == 0 || my_strcmp(command, "") == 0)
            command = getenv("HOME");
        status = chdir(command);
    }

    if (status != 0)
    {
        my_str("No directory specified, or directory doesn't exist. Please provide a directory that exists.\n");
    }
}
