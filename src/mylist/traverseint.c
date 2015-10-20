#include "mylist.h"

void traverse_int(struct s_node *head)
{
    if (head)
    {
        if ((head->elem))
        {
            my_int(*((int *)(head->elem)));
            my_char(' ');
        }
        traverse_int(head->next);
    }
}
