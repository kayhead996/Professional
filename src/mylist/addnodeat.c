#include "mylist.h"

void add_node_at(struct s_node *node, struct s_node **head, int n)
{
    if (head && node && node->elem && n >= 0) 
    {
        if (*head)
        {
            if (n == 0)
            {
                node->next = *head;
                node->prev = (*head)->prev;

                if (node->prev)
                    (node->prev)->next = node;

                (node->next)->prev = node;
            }

            else if (n > 0 && !((*head)->next))
            {
                (*head)->next = node;
                node->prev = *head;
                node->next = NULL;
            }
            else
                add_node_at(node, &((*head)->next), --n);
        }
        else
            *head = node;
    }
}
