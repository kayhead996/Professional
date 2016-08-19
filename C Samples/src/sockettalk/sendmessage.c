#include "sockettalk.h"

void send_message(int sent_fd, fd_set *fd_list, struct s_node *client_list, char *msg)
{
    int i, curr_fd, len, nodes;

    my_str(msg);
    len = my_strlen(msg);
    nodes = count_s_nodes(client_list);

    for (i = 0; i < nodes; i++)
    {
        curr_fd = ((struct chat_client *)elem_at(client_list, i))->fd;
        if (curr_fd != sent_fd && FD_ISSET(curr_fd, fd_list))
            send(curr_fd, msg, len, 0);
    }
}
