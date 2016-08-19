#include "sockettalk.h"

int main(int argc, char *argv[])
{
    int sock, len;
    char buffer[1024];
    struct sockaddr_in server;
    fd_set serv_connect;
    struct hostent *hp;

    if (argc == 3)
    {
        sock = socket(AF_INET, SOCK_STREAM, 0);

        if (sock < 0)
            error("Error opening socket");

        server.sin_family = AF_INET;
        hp = gethostbyname(argv[1]);

        if (hp == 0)
            error("Unknown host");

        bcopy(hp->h_addr, (char *)&server.sin_addr, hp->h_length);
        server.sin_port = htons(my_atoi(argv[2]));

        if (connect(sock, (struct sockaddr *)&server, sizeof(server)) < 0)
            error("Error on connect");

        do
        {
            bzero(buffer, 1024);
            FD_ZERO(&serv_connect);
            FD_SET(CLI_SOCK, &serv_connect);
            FD_SET(sock, &serv_connect);

            if (select(sock + 1, &serv_connect, NULL, NULL, NULL) < 0)
                error("Error with select");

            if (FD_ISSET(sock, &serv_connect))
            {
                bzero(buffer, 1024);
                len = read(sock, buffer, 1024);
                if (len < 0)
                    error("Error reading from socket");
                buffer[len] = '\0';

                my_str(buffer);
                if (my_strcmp(buffer, "Welcome! Please enter a username: ") != 0)
                    my_str("\n");
            }

            if (FD_ISSET(CLI_SOCK, &serv_connect))
                                    bzero(buffer, 1024);
                    len = read(STDIN_FILENO, buffer, 1024);
                    buffer[len-1] = '\0';

                if (len > 0)
                {
                    len = write(sock, buffer, 1024);
                    if (len < 0)
                        error("Error writing to socket");
                }

            }
        } while (my_strcmp(buffer, "/exit") != 0);
    }
    else
        error("Usage: ./client <hostname> <portnumber>");

    return 0;
}
