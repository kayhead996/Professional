#include "mylist.h"

void print_string(struct s_node *node)
{
    if (node)
        if (node->elem)
            my_str((char *)(node->elem));
}
