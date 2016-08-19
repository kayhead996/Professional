#ifndef _MYLIB_H_
#define _MYLIB_H_

#include <unistd.h>
#include <limits.h>
#include <stdlib.h>

#ifndef NULL
#define NULL ((void *)0)
#endif

void my_char(char );
void my_str(char *);
void my_int(int i);
void my_num_base(int , char *);
void my_num_base_rec(long, int, char *);
void my_alpha();
void my_digits();
int my_find(char *, char);
int my_rfind(char *, char);
int my_strlen(char *);
int my_revstr(char *);
char *my_strindex(char *, char);
char *my_strrindex(char *, char);
char *my_strcat(char *, char *);
int my_strcmp(char *, char *);
int my_strncmp(char *, char *, int);
char *my_strconcat(char *, char *);
char *my_strnconcat(char *, char *, int);
char *my_strcpy(char *, char *);
char *my_strncpy(char *, char *, int);
char *my_strdup(char *);
char *my_vect2str(char **);
char **my_str2vect(char *);
char *my_strreplace(char *, char *, char *);
int my_atoi(char *);
int my_maxstrlen(char **, int, int);
#endif
