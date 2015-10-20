#include "mylist.h"

void traverse_string(struct s_node *head)
{
    if (head)
    {
        if ((head->elem))
        {
            my_str((char *)(head->elem));
            my_char(' ');
        }
        traverse_string(head->next);
    }
}
