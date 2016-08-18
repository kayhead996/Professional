#include "mylist.h"

void *remove_last(struct s_node **head)
{
    void *ret = NULL;

    if (head && *head)
    {
        if ((*head)->next)
            ret = remove_last(&((*head)->next));
        else
        {
            ret = (*head)->elem;

            if ((*head)->prev)
                ((*head)->prev)->next = NULL;
            free(*head);
            *head = NULL;
        }
    }

    return ret;
}
