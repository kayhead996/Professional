#include "mylist.h"

void debug_string(struct s_node *head)
{
    if (head)
    {
        my_str("(");
        if (head->prev && (head->prev)->elem)
            my_str((char *)((head->prev)->elem));
        else
            my_str("NULL");
        my_str(" <- ");
        if (head->elem)
            my_str(((char *)(head->elem)));
        else
            my_str("NULL");
        my_str(" -> ");

        if (head->next)
        {
            my_str(((char *)((head->next)->elem)));
            my_str("), ");
        }
        else
            my_str("NULL)");
        debug_string(head->next);
    }
}
