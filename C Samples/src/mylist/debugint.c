#include "mylist.h"

void debug_int(struct s_node *head)
{
    if (head)
    {
        my_str("(");
        if (head->prev && (head->prev)->elem)
            my_int(*((int *)((head->prev)->elem)));
        else
            my_str("NULL");
        my_str(" <- ");
        if (head->elem)
            my_int(*((int *)(head->elem)));
        else
            my_str("NULL");
        my_str(" -> ");

        if (head->next)
        {
            my_int(*((int *)((head->next)->elem)));
            my_str("), ");
        }
        else
            my_str("NULL)");
        debug_int(head->next);
    }
}
