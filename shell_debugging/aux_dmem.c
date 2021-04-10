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
 * get_path - obtains directory path where command is executable.
 * @input_buffer: entire command being passed.
 * @path: pointer to path directory list.
 * Return: directory with concatenated input buffer.
 */
char *get_path(char *buffer, list_t **path)
{
	char *input, *aux, *command = NULL;
	char *slash_command, *slash_input, *input_buffer;
	struct stat status;
	list_t *list_pointer = *path;
	int i = 0;

	open_get_path();
	/* clean input in case that the first(s) chars are spaces */
	printf("--------> buffer = %s.\n", buffer);
	input_buffer = clean_spaces(buffer); // TODO liberar memoria alocada en clean_spaces
	printf("--------> input_buffer = %s.\n", input_buffer);
	input = strdup(input_buffer);
	printf("--------> input = %s.\n", input);
	input = strtok(input, "\n");
	printf("--------> input = %s.\n", input);
	// debug_1_get_path(input_buffer, input);
	free(input_buffer);
	/* extrae el primer argumento de input */
	aux = strdup(input);
	printf("--------> aux = %s.\n", aux);
	command = strtok(aux, " "); // TODO revisar
	if (command == NULL)
		command = aux;
	printf("--------> command = %s.\n", command);
	// debug_2_get_path(command);

	/* check if the first argument is executable */	
	if (stat(command, &status) == 0)
	{
		// debug_3_get_path();
		free (aux);
		return (input);
	}
	// debug_4_get_path();
	printf("--------> PASO PRIMER STAT");
	slash_command = concat("/", command);
	printf("--------> slash_command = %s.\n", slash_command);
	slash_input = concat("/", input);
	printf("--------> slash_input = %s.\n", slash_input);
	// debug_5_get_path(slash_command, slash_input);

	free(aux);
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
		//debug_6_get_path(aux);
		/* concatenar el resto de argumentos */
		free(aux);
		aux = concat(list_pointer->dir, slash_input);
		//debug_7_get_path(aux);
		free(input);
		free(slash_input);
		free(slash_command);
		return (aux);
	}
	// debug_8_get_path(command, input);
	free(slash_input);
	free(slash_command);
	//close_get_path();
	return (input);
}

/**
 * clean_spaces : remove spaces in the first positions of the buffer.
 * @buffer: buffer to clean.
 * Return: a new buffer iqual without the spaces in the fisrt(s) positions.
 */
char *clean_spaces(char *buffer)
{
	int len, first_char_position, i = 0;
	char *new_buffer, *true_buffer;

	new_buffer = strdup(buffer);
	if (new_buffer[0] != ' ')
		return (new_buffer);
	while (new_buffer[i] == ' ')
		i++;
	// i--;
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
	printf("------------> new_buffer = %s", true_buffer);
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
