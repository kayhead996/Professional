#include "terminfo.h"

int display_files(WINDOW **win, struct file **file_list)
{
    int i, x, y, row, col, start;

    getmaxyx(*win, row, col);
    clear();
    wmove(*win, 0, 0);
    for (i = 0, x = 0, y = 0, start = 0; file_list[i]; i++)
    {
        if (y < row)
        {
            if (file_list[i]->underline)
                attron(A_UNDERLINE);
            if (file_list[i]->highlight)
                attron(A_STANDOUT);
            file_list[i]->row = y;
            file_list[i]->col = x;
            mvwaddstr(*win, y++, x, file_list[i]->filename);
            if (file_list[i]->underline)
                attroff(A_UNDERLINE);
            if (file_list[i]->highlight)
                attroff(A_STANDOUT);
        }   
        else if (x < col)
        {
            x += maxstrlen(file_list, start, i);
            x += 8;
            y = 0;
            if (file_list[i]->underline)
                attron(A_UNDERLINE);
            if (file_list[i]->highlight)
                attron(A_STANDOUT);
            file_list[i]->row = y;
            file_list[i]->col = x;
            mvwaddstr(*win, y++, x, file_list[i]->filename);
            if (file_list[i]->underline)
                attroff(A_UNDERLINE);
            if (file_list[i]->highlight)
                attroff(A_STANDOUT);
            start = i;
        }
        else
        {
            werase(*win);
            return EXIT_FAILURE;
        }

        if (x + my_strlen(file_list[i]->filename) > col)
        {
            werase(*win);
            return EXIT_FAILURE;
        }
    }

    return EXIT_SUCCESS;
}
