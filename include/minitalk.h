#ifndef _MINITALK_H
#define _MINITALK_H_

#include "my.h"
#include <sys/types.h>
#include <signal.h>

int clientpid, gl_ack, currBit;
char currChar;
void server_exit(int signo);
void get_client_pid(int signo);
void get_client_char(int signo);
void client_error(int signo);
void sent_ack(int signo);

#endif
