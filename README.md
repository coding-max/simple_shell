### Files:

- main.c  
`int main(__attribute__((unused)) int ac, __attribute__((unused)) char **av, char **env)`  
`int start_shell(list_t *path, char **env)`  
`int execute_buffer(char *input_buffer, list_t *path, char **env)`  
`int execute_command(char *new_buffer, list_t *path, char **env, int final)`  

- main_shell.c  
`int only_execute(char *input_buffer, list_t *path)`  
`int start_shell(list_t *path)`  

- aux_list.c  
`list_t *list_path(char **env)`  
`list_t *create_list(char **environ)`  
`list_t *add_list(list_t **head, char *dir)`  
`void free_list(list_t *head)`  

- aux_dmem.c  
`char *get_path(char *buffer, list_t **path)`  
`char *aux_get_path(list_t *list_pointer, char *slash_command, char *slash_input, char *input)`  
`char *clean_spaces(char *buffer)`  
`char **create_argv(char *input_buffer, list_t **path)`  
`void free_argv(char **argv)`  

- aux_func.c  
`int check_builtin(char *command)`  
`int check_syntax(char *buffer)`  
`int builtins(char **input, char **env`)  
`void print_help(char **input`)  

- aux_str1.c  
`int str_len(char *s)`  
`char *str_cpy(char *dest, char *src)`  
`char *str_dup(char *str)`  
`char *str_cat(char *dest, char *src)`  
`char *str_con(char *s1, char *s2)`  

- aux_str2.c  
`int not_empty(char *input_buffer)`  
`int str_twins(char *s1, char *s2)`  
`int str_count(char *buffer)`  
`char *str_tr(char *buffer)`  
