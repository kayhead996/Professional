#include "mylist.h"

void *remove_node(struct s_node **head)
{
    void *ret = NULL;
    struct s_node *temp = new_node(NULL, NULL, NULL);

    if (head && *head)
    {
        ret = (*head)->elem;

        if ((*head)->next)
            temp = (*head)->next;

        temp->prev = (*head)->prev;

        if (!(temp->elem) && !(temp->next) && !(temp->prev))
        {
            free(temp);
            temp = NULL;
        }
        free(*head);

        *head = temp;
    }

    return ret;
}
