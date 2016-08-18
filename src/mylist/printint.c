#include "mylist.h"

void print_int(struct s_node *node)
{
    if (node)
        if (node->elem)
            my_int(*((int *)(node->elem)));
}
