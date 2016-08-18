#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char **argv)
{
    int pipefd[2], len = 0, status, i = 0;
    char str[100];
    pid_t pid;

    if (argc > 1)
    {
        pipe(pipefd);

        for (i = 1; i < argc; i++)
        {

            for (len = 0; argv[i][len] != '\0'; len++)
                ;

            write(pipefd[1], argv[i], len);

            if ((pid = fork()) == 0)
            {
                if ((pid = fork()) == 0)
                {
                    len = read(pipefd[0], str, 100);
                    write(1, str, len);
                    write(1, "\n", 1);
                    _exit(status);
                }
                else if (pid > 0)
                    waitpid(pid, &status, 0);
                else
                    write(1, "Fork failed\n", 12);
                _exit(status);
            }
            else if (pid > 0)
                waitpid(pid, &status, 0);
            else
                write(1, "Fork failed\n", 12);
        }

    }

    close(pipefd[0]);
    close(pipefd[1]);

    return 0;
}
