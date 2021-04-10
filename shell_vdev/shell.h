#ifndef SHELL_H
#define SHELL_H

#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>
#include <signal.h>

typedef struct list
{
	char* dir;
	struct list *next;
} list_t;

/* main_shell */
int only_execute(char *input_buffer, list_t *path);
int start_shell(list_t *path);

/* aux_list.c */
list_t *list_path(char **env);
list_t *add_to_list(list_t **head, char *dir);
void free_list(list_t *head);

/* aux_dmem.c */
char *get_path(char *buffer, list_t **path);
char *aux_get_path(list_t *list_pointer, char *slash_command, char *slash_input, char *input);
char *clean_spaces(char *buffer);
char **create_argv(char *input_buffer, list_t **path);
void free_argv(char **argv);

/* aux_str1.c */
int not_empty(char *input_buffer);
int _strtwins(char *s1, char *s2);

/* aux_str2.c */
int _strlen(char *s);
char *_strcpy(char *dest, char *src);
char *_strdup(char *str);
char* concat(const char *s1, const char *s2);

#endif