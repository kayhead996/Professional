#include "mylist.h"

int count_s_nodes(struct s_node *head)
{
    if (head)
        return 1 + count_s_nodes(head->next);
    return 0;
}
