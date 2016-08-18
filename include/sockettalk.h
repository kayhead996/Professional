#ifndef _SOCKETTALK_H_
#define _SOCKETTALK_H_

#include "mylist.h"
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <stdio.h>

#ifndef CLI_SOCK
#define CLI_SOCK 0
#endif

struct chat_client 
{
    char *username;
    int fd;
};

void bzero(char *buffer, size_t buff_size);
void bcopy(char *src, char *dst, size_t buff_size);
void error(const char *msg);
struct chat_client *new_client(char *name, int client_fd);
void change_username(struct chat_client *client, char *username);
void send_message(int sent_fd, fd_set *fd_list, struct s_node *client_list, char *msg);
int special(char *buffer);
#endif
