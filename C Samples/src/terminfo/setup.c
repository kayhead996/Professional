#include "terminfo.h"

struct file **setup(WINDOW **win, int file_listc, char *file_listv[])
{

    int err, i;
    struct file **file_list = NULL;

    keypad(*win, TRUE);
    werase(*win);

    file_list = (struct file **)malloc(file_listc * sizeof(struct file *));

    for (i = 1; file_listv[i] != NULL; i++)
    {
        file_list[i-1] = (struct file *)malloc(sizeof(struct file));
        file_list[i-1]->filename = my_strdup(file_listv[i]);

        file_list[i-1]->highlight = 0;
        if (i == 1)
            file_list[i-1]->underline = 1;
        else
            file_list[i-1]->underline = 0;

    }

    file_list[i-1] = NULL;

    while ((err = display_files(win, file_list)) == EXIT_FAILURE)
    {
        {
            clear();
            mvwaddstr(*win, 0, 0, "Please resize window");
            wrefresh(*win);
            pause();
        }
    }

    wmove(*win, 0, 0);

    return file_list;
}
