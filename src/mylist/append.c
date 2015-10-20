#include "mylist.h"

void append(struct s_node *node, struct s_node **head)
{
    if (head && node && node->elem)
    {
        if (*head)
            if (!(*head)->next)
            {
                node->prev = *head;
                (*head)->next = node;
            }
            else
                append(node, &((*head)->next));
        else
            *head = node;
    }
}
