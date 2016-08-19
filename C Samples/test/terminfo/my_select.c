#include "terminfo.h"

WINDOW *mainwin;
struct file **file_list = NULL;

void signalhandler(int signo)
{
}

int main(int argc, char *argv[])
{
    int ch;
    char *output = NULL;

    if (argc > 1)
    {
        if ((mainwin = initscr()) == NULL)
        {
            my_str("Error initializing ncurses\n");
            exit(EXIT_FAILURE);
        }

        noecho();
        file_list = setup(&mainwin, argc, argv);
        signal(SIGWINCH, resizehandler);
        signal(SIGINT, signalhandler);

        do 
        {
            wrefresh(mainwin);
            ch = getch();
            parse_key(&mainwin, ch, file_list, &output);
        }   while (ch != '\n' && ch != ESCAPE);

        delwin(mainwin);
        endwin();
        refresh();

        if (ch == '\n' && output)
        {
            write(STDIN_FILENO, output, my_strlen(output));
            free(output);
        }


    }
    else {
        my_str("Usage ./my_select <foldername>\n");
    }

    return 0;
}

void resizehandler(int signo)
{
    if (signo == SIGWINCH)
    {
        display_files(&mainwin, file_list);
        wrefresh(mainwin);
    }
}
