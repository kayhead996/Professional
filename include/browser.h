#ifndef _BROWSER_H_
#define _BROWSER_H_

#include <term.h>
#include <ncurses.h>
#include <signal.h>
#include "mylist.h"

void parse_key(WINDOW **win, int ch);
void setup(WINDOW **win);
#endif
