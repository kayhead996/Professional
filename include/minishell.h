#ifndef _MINISHELL_H_
#define _MINISHELL_H_

#include "my.h"
#include <sys/wait.h>

char *my_read();
void my_cd(char *);
void my_exec(char **);

#endif
