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

typedef struct list
{
	char* dir;
	struct list *next;
} list_t;

/* main_shell */
int only_execute(char *input_buffer, list_t *path);
int start_shell(list_t *path);

/* aux_list.c */
list_t *list_path(void);
list_t *add_to_list(list_t **head, char *dir);
void free_list(list_t *head);

/* aux_dmem.c */
char *get_path(char *input_buffer, list_t **path);
char **create_argv(char *input_buffer, list_t **path);
void free_argv(char **argv);

/* aux_str1.c */
int _strtwins(char *s1, char *s2);
int _strlen(char *s);
char *_strcpy(char *dest, char *src);
char *_strdup(char *str);

/* aux_str2.c */
int not_empty(char *input_buffer);
char* concat(const char *s1, const char *s2);

/* ANSI Colors */
#define RED printf("\033[0;31m");
#define GREEN printf("\033[0;32m");
#define YELLOW printf("\033[0;33m");
#define BLUE printf("\033[0;34m");
#define PURPLE printf("\033[0;35m");
#define CYAN printf("\033[0;36m");
#define RESET printf("\033[0m");

/* aux_style.c */
void style1(void);
void style2(void);
void style3(void);
void open_main(void);
void debug_main1(void);
void close_main(void);
void open_list_path(void);
void close_list_path(void);
void open_start_shell(void);
void prompt(void);
void debug_1_shell(void);
void debug_2_shell(void);
void debug_3_shell(void);
void debug_4_shell(void);
void debug_5_shell(int pid, char *str);
void debug_6_shell(void);
void debug_7_shell(int pid);
void debug_8_shell(int pid);
void debug_9_shell(int pid);
void close_start_shell(int pid);
void open_create_argv(void);
void debug_1_argv(char *input_buffer);
void debug_2_argv(char *new_input);
void debug_3_argv(int argc);
void debug_4_argv(char **argv);
void close_create_argv(void);
void open_get_path(void);
void debug_1_get_path(char *input_buffer, char *input);
void debug_2_get_path(char *command);
void debug_3_get_path(void);
void debug_4_get_path(void);
void debug_5_get_path(char *slash_command, char *slash_input);
void debug_6_get_path(char *aux);
void debug_7_get_path(char *aux);
void debug_8_get_path(char *command, char *input);
void close_get_path(void);
#endif
