#include "mylist.h"

void *elem_at(struct s_node *head, int n)
{
    void *ret = NULL;

    if (head && n >= 0)
    {
        if (n == 0 || !(head->next))
            ret = head->elem;
        else
            ret = elem_at(head->next, --n);
    }

    return ret;
}
