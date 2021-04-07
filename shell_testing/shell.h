#ifndef SHELL_H
#define SHELL_H

#include <unistd.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <errno.h>

#define RED printf("\033[0;31m");
#define BLUE printf("\033[0;34m");
#define GREEN printf("\033[0;32m");
#define PURPLE printf("\033[0;35m");
#define RESET printf("\033[0m");

typedef struct list
{
	char* dir;
	struct list *next;
} list_t;

/* main_shell */ //* 2/5 */
int only_execute(char *input_buffer, list_t *path);
int start_shell(list_t *path);

/* aux_list.c //* 3/5 */
list_t *list_path(void);
list_t *add_to_list(list_t **head, char *dir);
void free_list(list_t *head);

/* aux_dmem.c //* 3/5 */
char *get_path(char *input_buffer, list_t **path);
char **create_argv(char *input_buffer, list_t **path);
void free_argv(char **argv);

/* aux_string.c // TODO realloc functions */
char *_strcpy(char *dest, char *src);
char *_strdup(char *str);
char* concat(const char *s1, const char *s2);
int not_empty(char *input_buffer);
int _strtwins(char *s1, char *s2);
int _strlen(char *s);

/* aux_style.c */
void style1(void);
void style2(void);
void style3(void);

#endif
