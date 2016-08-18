#include "mylist.h"

struct s_node *node_at(struct s_node *head, int n)
{
    struct s_node *temp = NULL;

    if (head && n >= 0)
    {
        if (n == 0 || !(head->next))
            temp = head;
        else
            temp = node_at(head->next, --n);
    }

    return temp;
}
