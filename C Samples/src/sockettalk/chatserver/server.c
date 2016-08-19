#include "sockettalk.h"

int main(int argc, char *argv[])
{
    int sock, portnum, len, new_client_fd, curr_fd, i, j, max_fd, num_clients, temp_fd;
    char *username;
    char buffer[1024];
    char *output = NULL;
    struct sockaddr_in server, client;
    fd_set connect;
    socklen_t socklength;
    struct s_node *chat_clients = NULL;

    if (argc > 1)
    {
        if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
            error("Error opening socket");

        portnum = my_atoi(argv[1]);

        bzero((char *)&server, sizeof(server));

        server.sin_family = AF_INET;
        server.sin_port = htons(portnum);
        server.sin_addr.s_addr = INADDR_ANY;

        if (bind(sock, (struct sockaddr *)&server, sizeof(server)) < 0)
            error("Bind error");

        socklength = sizeof(server);
        if (getsockname(sock, (struct sockaddr *)&server, &socklength))
            error("Error getting socket name");

        gethostname(buffer, 1024);

        my_str("Chat server is on port: ");
        my_int(ntohs(server.sin_port));
        my_str(" on host: ");
        my_str(buffer);
        my_str("\n");

        bzero(buffer, 1024);
        listen(sock, 5);

        while (1)
        {
            new_client_fd = 0;

            FD_ZERO(&connect);

            FD_SET(sock, &connect);
            max_fd = sock;

            num_clients = count_s_nodes(chat_clients);

            for (i = 0; i < num_clients; i++)
            {
                curr_fd = ((struct chat_client *)elem_at(chat_clients, i))->fd;

                if (curr_fd > 0)
                    FD_SET(curr_fd, &connect);

                if (curr_fd > max_fd)
                    max_fd = curr_fd;
            }

            if (select(max_fd + 1, &connect, NULL, NULL, NULL) < 0)
                error("Error with select");

            if (FD_ISSET(sock, &connect))
            {
                socklength = sizeof(client);
                new_client_fd = accept(sock, (struct sockaddr *)&client, &socklength);

                output = my_strconcat(buffer, "Welcome! Please enter a username: ");
                if (send(new_client_fd, output, my_strlen(output), 0) < 0)
                    error("Error on send");
                free(output);

                if (new_client_fd < 0)
                    error("Error on accept");

                if ((len = read(new_client_fd, buffer, 1024)) < 0)
                    error("Error reading message");
                else if (len == 0)
                    my_str("Ending connection\n");
                else
                {
                    buffer[len] = '\0';
                    output = my_strconcat(output, buffer);
                    output = my_strconcat(output, " has joined");

                    add_elem((void *)new_client(buffer, new_client_fd), &chat_clients);

                    num_clients = count_s_nodes(chat_clients);
                    for (j = 0; j < num_clients; j++)
                    {
                        curr_fd = ((struct chat_client *)elem_at(chat_clients, j))->fd;
                        send(curr_fd, output, my_strlen(output), 0);
                    }
                    free(output);
                    output = NULL;
                }
            }

            num_clients = count_s_nodes(chat_clients);

            for (i = 0; i < num_clients; i++)
            {
                bzero(buffer, 1024);
                if (elem_at(chat_clients, i))
                {
                    curr_fd = ((struct chat_client *)elem_at(chat_clients, i))->fd;
                    username = ((struct chat_client *)elem_at(chat_clients, i))->username;
                }
                if (curr_fd != new_client_fd && FD_ISSET(curr_fd, &connect))
                {
                    if ((len = read(curr_fd, buffer, 1024)) == 0)
                    {
                        output = my_strconcat(output, username);
                        output = my_strconcat(output, " has left the chat");

                        close(curr_fd);
                        remove_node_at(&chat_clients, i);

                        num_clients = count_s_nodes(chat_clients);
                        for (j = 0; j < num_clients; j++)
                        {
                            if (elem_at(chat_clients, j))
                            {
                                temp_fd = ((struct chat_client *)elem_at(chat_clients, j))->fd;
                                send(temp_fd, output, my_strlen(output), 0);
                            }
                        }

                        if (output)
                        {
                            free(output);
                            output = NULL;
                        }

                    }
                    else
                    {
                        buffer[len] = '\0';

                        if (special(buffer) == 0)
                        {
                            output = my_strconcat(output, username);
                            output = my_strconcat(output, ": ");
                            output = my_strconcat(output, buffer);
                        }
                        else if (my_strncmp(buffer, "/me", 3) == 0)
                        {
                            output = my_strconcat(output, username);
                            output = my_strconcat(output, " ");
                            username = my_strindex(buffer, ' ');
                            username++;
                            output = my_strconcat(output, username);
                        }
                        else if (my_strncmp(buffer, "/nick", 5) == 0)
                        {
                            output = (char *)malloc(sizeof(char) * my_strlen(username)+1);
                            output = my_strcpy(output, username);
                            username = my_strindex(buffer, ' ');

                            if (username)
                            {
                                username++;
                                if (elem_at(chat_clients, i))
                                {
                                    change_username((struct chat_client *)elem_at(chat_clients, i), username);
                                    username = my_strcpy(username, "Username changed to ");
                                    username = my_strconcat(username, ((struct chat_client *)elem_at(chat_clients, i))->username);
                                    send(curr_fd, username, my_strlen(username), 0);

                                    output = my_strconcat(output, " has changed their name to ");
                                    output = my_strconcat(output, ((struct chat_client *)elem_at(chat_clients, i))->username);
                                }
                            }
                        }

                        for (j = 0; j < num_clients; j++)
                        {
                            if (elem_at(chat_clients, j))
                                temp_fd = ((struct chat_client *)elem_at(chat_clients, j))->fd;
                            if (output && temp_fd != curr_fd)
                                send(temp_fd, output, my_strlen(output), 0);
                        }

                        if (output)
                        {
                            free(output);
                            output = NULL;
                        }
                    }
                }
            } 

        }
    }
    else
        my_str("Usage: ./server <port>\n");

    return 0;
}
