#ifndef _TERMINFO_H_
#define _TERMINFO_H_

#include <term.h>
#include <ncurses.h>
#include <signal.h>
#include "my.h"

#define ESCAPE 27

struct file 
{
    char *filename;
    int underline;
    int highlight;
    int row;
    int col;
};

struct file **setup(WINDOW **win, int file_listc, char *file_listv[]);
int display_files(WINDOW **win, struct file **file_list);
void parse_key(WINDOW **win, int ch, struct file **file_list, char **output);
void resizehandler(int signo);
int maxstrlen(struct file **file_list, int start, int end);
void move_cursor(WINDOW **win, int ch, struct file **file_list);
void save_output(struct file **file_list, char **output);
void highlight_file(WINDOW **win, struct file **file_list);
#endif
