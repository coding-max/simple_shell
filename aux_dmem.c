#include "shell.h"

/**
 * create_argv - turns input_buffer into argument vector.
 * @input_buffer: input_buffer to be processed.
 * @path: pointer to path directory list.
 * Return: a pointer to the new argument vector.
 */
char **create_argv(char *input_buffer, list_t **path)
{
	int i = 0,  ac = 0, argc = 1;
	char *current_string, *str_to_put, *new_input;
	char **argv;

	new_input = get_path(input_buffer, path);

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
	free(new_input);
	return (argv);
}

/**
 * get_path - obtains directory path where command is executable.
 * @input_buffer: entire command being passed.
 * @path: pointer to path directory list.
 * Return: directory with concatenated input buffer.
 */
char *get_path(char *input_buffer, list_t **path)
{
	char *input, *aux, *command = NULL;
	char *slash_command, *slash_input;
	struct stat status;

	input = strdup(input_buffer);
	input = strtok(input, "\n");

	/* extrae el primer argumento de input */
	command = strtok(input_buffer, "\n");
	aux = strtok(command, " ");
	if (aux)
		command = aux;

	/* check if the first argument is executable */
	if (stat(command, &status) == 0)
	{
		return (input);
	}

	slash_command = concat("/", command);
	slash_input = concat("/", input);

	return (get_path_aux(aux, slash_command, slash_input, input, path));
}

/**
 * get_path_aux - auxiliary function for obtains directory path.
 * @aux: auxiliary string.
 * @slash_command: auxiliary string.
 * @slash_input: auxiliary string.
 * @input: auxiliary string.
 * @path: pointer to path directory list.
 * Return: directory with concatenated input buffer.
 */
char *get_path_aux(char *aux, char *slash_command,
			char *slash_input, char *input, list_t **path)
{
	list_t *list_pointer = *path;
	struct stat status;

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
		/* concatenar el resto de argumentos */
		free(aux);
		aux = concat(list_pointer->dir, slash_input);
		free(input);
		free(slash_input);
		free(slash_command);
		return (aux);
	}
	free(slash_input);
	free(slash_command);
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
