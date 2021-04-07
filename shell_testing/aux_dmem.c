#include "shell.h"

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

	style2();
	printf("\n");
	style2();
	BLUE;
	printf("get_path runing...\n");
	RESET;

	input = strdup(input_buffer);
	input = strtok(input, "\n");
	style3();
	printf("input_buffer = %s", input_buffer);
	style3();
	printf("input = %s.\n", input);

	/* extrae el primer argumento de input */
	command = strtok(input_buffer, "\n");
	aux = strtok(command, " ");
	if (aux)
		command = aux;
	style3();
	printf("command = %s.\n", command);

	BLUE;
	/* check if the first argument is executable */	
	if (stat(command, &status) == 0) 
	{ 
		style3();
		printf("command executable.\n");
		return (input);  // TODO
	}
	style3();
	printf("command NOT excutable.\n");
	RESET; 
 
	slash_command = concat("/", command);
	slash_input = concat("/", input);
	style3();
	printf("slash_command = %s.\n", slash_command);
	style3();
	printf("slash_input = %s.\n", slash_input);
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
		style3();
		printf("command (%s) it's executable\n", aux);
		RESET;
		/* concatenar el resto de argumentos */
		free(aux);
		aux = concat(list_pointer->dir, slash_input);
		style3();
		printf("command to return:(%s)\n", aux);
		style2();
		BLUE;
		printf("get_path clossing...\n");
		RESET;
		free(input);
		free(slash_input);
		free(slash_command);
		return (aux);
	}
	style3();
	printf("command: (%s) it's NOT executable in any directory\n", command);
	style3();
	printf("command to return:(%s)\n", input);

	free(slash_input);
	free(slash_command); 
	style2();
	BLUE;
	printf("clossing...\n");
	RESET;
	return (input);
}

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
	
	style1();
	printf("\n");
	style1();
	PURPLE;
	printf("create_argv runing...\n");
	RESET;

	style2();
	printf("input_buffer = %s", input_buffer);
	new_input = get_path(input_buffer, path);
	style2();
	printf("\n");
	style2();
	printf("new_input = %s\n", new_input);

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
	style2();
	printf("arguments detected: %i\n", argc);
	argv = malloc(sizeof(char *) * (argc + 1));
	if (argv == NULL)
	{
		/* TODO print error */
		write(STDOUT_FILENO, "MALLOC ERROR\n", 14);
		return (NULL);
	}

	// TODO la func que busca el path no le quieta el \n antes de retornar?
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

	style2();
	printf("argument vector:\n");

	i = 0;
	while (argv[i])
	{
		style2();
		printf("   [%i] = %s.\n", i, argv[i]);
		i++;
	}

	style1();
	PURPLE;
	printf("create_argv clossing...\n");
	RESET;
	free(new_input);
	return (argv);
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
