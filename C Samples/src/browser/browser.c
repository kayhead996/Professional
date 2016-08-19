#include "browser.h"

int main(int argc, char *argv[])
{
    int ch;
    char *output = NULL;
    WINDOW *mainwin;

    if ((mainwin = initscr()) == NULL)
    {
        my_str("Error initializing ncurses\n");
        exit(EXIT_FAILURE);
    }

    noecho();
    setup(&mainwin);

    do 
    {
        wrefresh(mainwin);
        ch = getch();
        parse_key(&mainwin, ch);
    }   while (ch != '\n' && ch != ESCAPE);

    delwin(mainwin);
    endwin();
    refresh();


    return 0;
}
