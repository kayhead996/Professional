#include "mylist.h"

void traverse_char(struct s_node *head)
{
    if (head)
    {
        if ((head->elem))
        {
            my_char(*((char *)(head->elem)));
            my_char(' ');
        }
        traverse_char(head->next);
    }
}
