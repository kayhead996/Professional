#include "mylist.h"

void add_node(struct s_node *node, struct s_node **head)
{
    if (head && node && node->elem)
    {
        if (!(*head))
        {
            *head = node;
            (*head)->prev = NULL;
        }
        else if ((*head)->elem)
        {
            node->next = *head;
            (*head)->prev = node;
            (*head) = node;
        }
        else
            (*head)->elem = node->elem;
    }
}
