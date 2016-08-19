#include "terminfo.h"

void move_cursor(WINDOW **win, int ch, struct file **file_list)
{
    int i, x, y, oldX, oldY, change_row;

    getyx(*win, y, x);

    for (i = 0; file_list[i] != NULL; i++)
        file_list[i]->underline = 0;

    if (ch == KEY_UP)
    {
        if (y != 0)
            y--;
        else
        {
            oldX = --i;
            for (; i >= 0; i--)
                if (file_list[i]->col < x || (x == 0 && i == oldX))
                {
                    y = file_list[i]->row;
                    x = file_list[i]->col;
                    break;
                }
        }
    }
    else if (ch == KEY_DOWN)
    {
        oldY = y;

        for (i = 0; file_list[i] != NULL; i++)
            if (file_list[i]->col == x && file_list[i]->row > y)
            {
                y = file_list[i]->row;
                break;
            }

        if (y == oldY)
        {
            for (i = 0; file_list[i] != NULL; i++)
                if (file_list[i]->col > x)
                {
                    x = file_list[i]->col;
                    y = file_list[i]->row;
                    break;
                }

            if (y == oldY)
            {
                x = 0;
                y = 0;
            }
        }


    }
    else if (ch == KEY_LEFT)
    {
        if (x != 0)
        {
            for (i -= 1; i >= 0; i--)
                if (file_list[i]->col < x)
                {
                    x = file_list[i]->col;
                    break;
                }
        }
        else 
            y = 0;
    }
    else if (ch == KEY_RIGHT)
    {
        oldX = x;
        for (i = 0; file_list[i] != NULL; i++)
        {
            if (file_list[i]->col > x)
            {
                x = file_list[i]->col;
                break;
            }
        }

        if (x == oldX)
            y = file_list[i-1]->row;
        else
        {
            change_row = 0;
            for (i = 0; file_list[i] != NULL; i++)
            {
                if (file_list[i]->col == x && file_list[i]->row == y)
                {
                    change_row = 0;
                    break;
                }
                else if (file_list[i]->col == x && file_list[i]->row != y)
                {
                    change_row = 1;
                    oldY = file_list[i]->row;
                }
            }

            if (change_row == 1)
                y = oldY;

        }

    }

    for (i = 0; file_list[i] != NULL; i++)
        if (file_list[i]->row == y && file_list[i]->col == x)
            file_list[i]->underline = 1;
    display_files(win, file_list);
    wmove(*win, y, x);
    wrefresh(*win);
}
