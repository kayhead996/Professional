#include "mylist.h"

void add_elem(void *elem, struct s_node **head)
{
    if (elem && head)
        add_node(new_node(elem, NULL, NULL), head);
}
