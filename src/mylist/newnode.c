#include "mylist.h"

struct s_node *new_node(void *elem, struct s_node *next, struct s_node *previous)
{
    struct s_node *node = (struct s_node *)malloc(sizeof(struct s_node));
    node->elem = elem;
    node->next = next;
    node->prev = previous;

    return node;
}
