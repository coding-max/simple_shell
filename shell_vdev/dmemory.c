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
		str_to_put = str_dup(current_string);
		argv[ac] = str_to_put;
		current_string = strtok(NULL, " ");
		ac++;

	}
	free(new_input);
	return (argv);
}

/**
 * get_path - obtains directory path where command is executable.
 * @buffer: entire command being passed.
 * @path: pointer to path directory list.
 * Return: directory with concatenated input buffer.
 */
char *get_path(char *buffer, list_t **path)
{
	char *input, *aux, *command = NULL;
	char *slash_command, *slash_input, *input_buffer;
	struct stat status;
	list_t *list_pointer = *path;

	/* clean input in case that the first(s) chars are spaces */
	input_buffer = clean_spaces(buffer);
	input = str_dup(input_buffer);
	free(input_buffer);

	/* extrae el primer argumento de input */
	aux = str_dup(input);
	command = strtok(aux, " ");
	if (command == NULL)
		command = aux;

	/* check if the first argument is executable */
	if (stat(command, &status) == 0)
	{
		free(aux);
		return (input);
	}
	/* check if the first argument is a builtin command */
	if (check_builtin(command) == 0)
	{
		free(aux);
		return (input);
	}
	slash_command = str_con("/", command);
	slash_input = str_con("/", input);

	free(aux);
	return (aux_get_path(list_pointer, slash_command, slash_input, input));
}


/**
 * aux_get_path - auxiliary function for obtains directory path.
 * @list_pointer: pointer to directory in path list.
 * @slash_command: auxiliary string.
 * @slash_input: auxiliary string.
 * @input: auxiliary string.
 * Return: directory with concatenated input buffer.
 */
char *aux_get_path(list_t *list_pointer, char *slash_command,
			char *slash_input, char *input)
{
	char *aux;
	struct stat status;

	while (list_pointer) /* does not reach the end of the list */
	{
		/* check if command is executable in $list_pointer->dir */
		aux = str_con(list_pointer->dir, slash_command);
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
		aux = str_con(list_pointer->dir, slash_input);
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
 * clean_spaces - remove spaces in the first position of the buffer.
 * @buffer: buffer to be cleaned.
 * Return: a new buffer equal without spaces in the first position(s).
 */
char *clean_spaces(char *buffer)
{
	int len, first_char_position, i = 0;
	char *new_buffer, *true_buffer;

	new_buffer = str_dup(buffer);
	if (new_buffer[0] != ' ')
		return (new_buffer);
	while (new_buffer[i] == ' ')
		i++;
	first_char_position = i;
	while (new_buffer[i])
		i++;
	len = i - first_char_position;
	true_buffer = malloc(sizeof(char) * (len + 1));
	i = first_char_position;
	while (new_buffer[i])
	{
		true_buffer[i - first_char_position] = new_buffer[i];
		i++;
	}
	true_buffer[i - first_char_position] = '\0';
	free(new_buffer);
	return (true_buffer);
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
