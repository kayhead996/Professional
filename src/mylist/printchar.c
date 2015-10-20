#include "mylist.h"

void print_char(struct s_node *node)
{
    if (node)
        if (node->elem)
            my_char(*((char *)(node->elem)));
}
