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
int start_shell(char **env);


/* functions in aux_strings.c */ //* full
int _strtwins(char *s1, char *s2);
int _strlen(char *s);
char *_strcpy(char *dest, char *src);
char *_strdup(char *str);
char **_strtoargv(char *input_buffer);

#endif
