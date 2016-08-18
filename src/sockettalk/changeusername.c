#include "sockettalk.h"

void change_username(struct chat_client *client, char *username)
{
    int size;
    
    free(client->username);
    client->username = NULL;

    size = my_strlen(username) + 1;
    client->username = (char *)malloc(sizeof(char) * size);
    client->username = my_strcpy(client->username, username);
}
