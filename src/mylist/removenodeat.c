#include "mylist.h"

void *remove_node_at(struct s_node **head, int n)
{
    void *ret = NULL;

    if (head && *head && n >= 0)
    {
        if (n == 0 || !((*head)->next))
        {
            ret = (*head)->elem;

            if ((*head)->next)
                ((*head)->next)->prev = (*head)->prev;

            if ((*head)->prev)
                ((*head)->prev)->next = (*head)->next;

            free(*head);
            *head = NULL;

        }
        else 
            ret = remove_node_at(&((*head)->next), --n);
    }


    return ret;
}
