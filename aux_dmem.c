#include "shell.h"

// TODO comments and description
char **create_argv(char *input_buffer)
{
	int i = 0,  ac = 0;
	int argc = 1; // siempe hay al menos un argumento (nombre del programa)
	char **argv; // aca se van a cargar los argumentos
	char *current_string;
	char *str_to_put;

	while(input_buffer[i])
	{
		if (input_buffer[i] == ' ' && (input_buffer[i + 1] && (input_buffer[i + 1] != ' ' && input_buffer[i + 1] != '\n')))
			argc += 1;
		i++;
	}

	argv = malloc (sizeof(char*) * (argc + 1));
	if (argv == NULL)
	{
		// TODO print error
		write(STDOUT_FILENO, "MALLOC ERROR\n", 14);
		return (NULL);
	}
	
	current_string = strtok(input_buffer, "\n");
	current_string = strtok(current_string, " "); // primer argumento
	while (ac < (argc + 1))
	{
		str_to_put = _strdup(current_string);
		argv[ac] = str_to_put;
		current_string = strtok(NULL, " ");
		ac++;
		
	}

	return (argv);
}

// TODO comments and description
void free_argv(char **argv)
{
	int i = 0;

	while(argv[i])
	{
		free(argv[i]);
		i++;
	}
	free(argv);
}