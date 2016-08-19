#include "minishell.h"

int main()
{
    int exitStatus = 0;
    char *cwd;
    char **commandVect;
    char *formattedDir;
    char *input;

    while(!exitStatus)
    {
        if ((cwd = getcwd(NULL, 0)))
        {
            my_str("keyurshell "); 
            formattedDir = my_strreplace(cwd, getenv("HOME"), "~");
            if (formattedDir && formattedDir[0] != '\0')
                my_str(formattedDir);
            else
                my_str(cwd);
            my_str("> ");
        }
        else
        {
            my_str("getcwd() error\n");
            exitStatus = 1;
        }

        if (!exitStatus)
        {

            input = my_read();

            if (my_strlen(input) > 0 && my_strcmp(input, "\n") != 0)
            {
                commandVect = my_str2vect(input);
                if (my_strcmp(commandVect[0], "cd") == 0 || my_strcmp(commandVect[0], "cd\n") == 0)
                {
                    if (my_strindex(commandVect[1], '~'))
                        commandVect[1] = my_strreplace(commandVect[1], "~", getenv("HOME"));
                    my_cd(commandVect[1]);
                }
                else if (my_strcmp(commandVect[0], "exit") == 0)
                    exitStatus = 1;
                else
                    my_exec(commandVect);
            }
        }

    }

    free(cwd);
    free(formattedDir);

    return 0;
}
