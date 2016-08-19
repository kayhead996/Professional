#include "sockettalk.h"

struct chat_client *new_client(char *name, int client_fd)
{
    struct chat_client *client = (struct chat_client *)malloc(sizeof(struct chat_client));
    int size;
    
    size = my_strlen(name) + 1;

    client->username = (char *)malloc(sizeof(char) * size);
    client->username = my_strcpy(client->username, name);
    client->fd = client_fd;

    return client;
}
