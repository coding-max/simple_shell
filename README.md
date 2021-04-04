<img style="text-align:center" src="https://github.com/coding-max/simple_shell/blob/develop/assets/flowchart.svg?raw=true" alt="flowchart of main.c"/>  

### Files:

- main.c  
`int main(int ac, char **av, char **env)`  

- main_shell.c  
`int start_shell(char **env)`  
`int only_execute(char *input_buffer)`  

- aux_string.c  
`int _strtwins(char *s1, char *s2)`  
`int _strlen(char *s)`  
`char *_strcpy(char *dest, char *src)`  
`char *_strdup(char *str)`  

- aux_dmem.c  
`char **create_argv(char *input_buffer)`  
`void free_argv(char **argv)`  