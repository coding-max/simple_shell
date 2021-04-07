#include "shell.h"

/**
 * create_argv - turns input_buffer into argument vector.
 * @input_buffer: input_buffer to be processed.
 * Return: a pointer to the new argument vector.
 */
char **create_argv(char *input_buffer, list_t **path)
{
	int i = 0,  ac = 0, argc = 1;
	char *current_string, *str_to_put, *new_input;
	char **argv;
	
	open_create_argv();
	debug_1_argv(input_buffer);
	new_input = get_path(input_buffer, path);
	debug_2_argv(new_input);

	while (new_input[i])
	{
		/**
		 * counter increases if current position is a space
		 * and following position not NULL, space nor \n
		 */
		if (new_input[i] == ' ' &&
			(new_input[i + 1] &&
				(new_input[i + 1] != ' ' &&
					new_input[i + 1] != '\n')))
			argc += 1;
		i++;
	}

	debug_3_argv(argc);
	argv = malloc(sizeof(char *) * (argc + 1));
	if (argv == NULL)
	{
		write(STDOUT_FILENO, "MALLOC ERROR\n", 14);
		return (NULL);
	}

	current_string = strtok(new_input, "\n");
	current_string = strtok(current_string, " ");
	/* adds arguments to array */
	while (ac < (argc + 1))
	{
		/* duplicates argument and adds it to array */
		str_to_put = _strdup(current_string);
		argv[ac] = str_to_put;
		current_string = strtok(NULL, " ");
		ac++;

	}

	debug_4_argv(argv);
	free(new_input);
	close_create_argv();
	return (argv);
}

/**
 * get_path - idk
 * @input_buffer: idk
 * @path: idk
 * Return: idk
 */
char *get_path(char *input_buffer, list_t **path)
{
	char *input, *aux, *command = NULL;
	char* slash_command, *slash_input;
	struct stat status;
	list_t *list_pointer = *path; 
	int i = 0;

	open_get_path();
	input = strdup(input_buffer);
	input = strtok(input, "\n");
	debug_1_get_path(input_buffer, input);

	/* extrae el primer argumento de input */
	command = strtok(input_buffer, "\n");
	aux = strtok(command, " ");
	if (aux)
		command = aux;
	debug_2_get_path(command);

	/* check if the first argument is executable */	
	if (stat(command, &status) == 0) 
	{ 
		debug_3_get_path();
		return (input);
	}
	debug_4_get_path();
 
	slash_command = concat("/", command);
	slash_input = concat("/", input);
	debug_5_get_path(slash_command, slash_input);

	while (list_pointer) /* does not reach the end of the list */
	{
		/* check if command is executable in $list_pointer->dir */
		aux = concat(list_pointer->dir, slash_command);
		if (stat(aux, &status) == 0)
			break;
		free(aux);
		list_pointer = list_pointer->next;
	}
	/* check if command is executable */
	if (list_pointer && (stat(aux, &status) == 0))
	{
		debug_6_get_path(aux);
		/* concatenar el resto de argumentos */
		free(aux);
		aux = concat(list_pointer->dir, slash_input);
		debug_7_get_path(aux);
		free(input);
		free(slash_input);
		free(slash_command);
		return (aux);
	}
	debug_8_get_path(command, input);
	free(slash_input);
	free(slash_command); 
	close_get_path();
	return (input);
}

/**
 * free_argv - frees memory allocated in argument vector.
 * @argv: argument vector to be freed.
 */
void free_argv(char **argv)
{
	int i = 0;

	while (argv[i])
	{
		free(argv[i]);
		i++;
	}
	free(argv);
}
