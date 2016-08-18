#include "terminfo.h"

int maxstrlen(struct file **file_list, int start, int end)
{
    int max, i;

    for (max = 0, i = 0; file_list[i] != NULL; i++)
        if (my_strlen(file_list[i]->filename) > max)
            max = my_strlen(file_list[i]->filename);

    return max;
}
