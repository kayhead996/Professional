#include "mylist.h"

void empty_list(struct s_node **head)
{
    while (*head)
        remove_node(head);
}
