#include "terminfo.h"

void parse_key(WINDOW **win, int ch, struct file **file_list, char **output)
{
    switch(ch)
    {
        case KEY_DOWN: 
            move_cursor(win, ch, file_list);
            break;
        case KEY_UP:
            move_cursor(win, ch, file_list);
            break;
        case KEY_LEFT:
            move_cursor(win, ch, file_list);
            break;
        case KEY_RIGHT:
            move_cursor(win, ch, file_list);
            break;
        case '\n':
            save_output(file_list, output);
            break;
        case ' ':
            highlight_file(win, file_list);
            break;
    }
}
