#include "terminfo.h"

void highlight_file(WINDOW **win, struct file **file_list)
{
    int i, x, y;

    getyx(*win, y, x);

    for (i = 0; file_list[i] != NULL; i++)
        if (file_list[i]->row == y && file_list[i]->col == x)
            file_list[i]->highlight = file_list[i]->highlight == 0? 1 : 0;

    display_files(win, file_list);
    wmove(*win, y, x);
    wrefresh(*win);
}
