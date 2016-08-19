#include "terminfo.h"

void save_output(struct file **file_list, char **output)
{
    int i, size;

    for (i = 0, size = 0; file_list[i]; i++)
        if (file_list[i]->highlight == 1)
        {
            size += my_strlen(file_list[i]->filename);
            size++;
        }

    if (size > 0)
    {
        *output = (char *)malloc(size * sizeof(char));


        for (i = 0; file_list[i] != NULL; i++)
        {
            if (file_list[i]->highlight == 1)
            {
                *output = my_strcat(*output, file_list[i]->filename);
                *output = my_strcat(*output, " ");
            }
        }

        *output = my_strcat(*output, "\0");
    }
}
