#ifndef SHELL_H
#define SHELL_H

#include <unistd.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>

/* calls in main */
int only_execute(char *input_buffer);
int start_shell(void);


/* functions in aux_strings.c */ //* 4/5
int _strtwins(char *s1, char *s2);
int _strlen(char *s);
char *_strcpy(char *dest, char *src);
char *_strdup(char *str);

/* funtions in aux_dmem.c */ //* 2/5
char **create_argv(char *input_buffer);
void free_argv(char **argv);

#endif
