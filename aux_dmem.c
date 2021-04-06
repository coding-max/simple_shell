#include "shell.h"

/**
* list_path - 
*/
list_t *list_path(void)
{
	list_t *head = NULL, *node = NULL;
	extern char **environ;
	char *var_name = NULL;
	char *var_value = NULL;
	char *dir;
	int i = 0;

	GREEN;
	printf("\nlist_path runnig...\n");
	RESET;
	while (environ[i])
	{
		var_name = strtok(environ[i], "=");
		if (_strtwins(var_name, "PATH") == 0)
		{
			var_value = strtok(NULL, "\n");
			break;
		}
		i++;
	}

	printf("list_path -> var_name = %s\n", var_name);
	printf("list_path -> var_value = %s\n", var_value);

	BLUE;
	if (var_value)
	{
		dir = strtok(var_value, ":");
		printf("     list_path -> dir = %s\n", dir);
		head = add_to_list(&head, dir);
		while (dir)
		{
			node = add_to_list(&head, dir);
			dir = strtok(NULL, ":");
			printf("     list_path -> dir = %s\n", dir);
		}
		/* TODO añadir ultimo dir en PATH */
	}
	else
	printf("list_path -> ERROR: var_value NULL\n");
	RED;
	printf("list_path clossing...\n");
	RESET;
	return (head);
}

list_t *add_to_list(list_t **head, char *dir)
{
	list_t *new, *aux = *head;

	new = malloc(sizeof(list_t));
	if (new == NULL)
	{
		printf("add_to_list -> ERROR: unable to allocate memory\n");
		return (NULL);
	}
	new->dir = dir;
	new->next = NULL;

	if (aux)
	{
		while (aux->next)
			aux = aux->next;
		aux->next = new;
	}
	else
		*head = new;

	return (new);
}

/**
 * free_listint - free list
 * @head: head
 * Return: into the void
 */
void free_list(list_t *head)
{
	list_t *actual_node;
	list_t *next_node;

	GREEN;
	printf("\nfree_list runnig...\n");
	RESET;
	if (head)
	{
		actual_node = head;
		next_node = head->next;
		while (next_node)
		{
			// printf("free_list -> before free: %s\n", actual_node->dir);
			free(actual_node->dir);
			// printf("free_list -> after free: %s\n", actual_node->dir);
			free(actual_node);
			actual_node = next_node;
			next_node = next_node->next;
		}
		free(actual_node->dir);
		free(actual_node);
	}
	RED;
	printf("free_list clossing...\n");
	RESET;
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

	GREEN;
	printf("\nget_path runing...\n");
	RESET;
	printf("get_path -> path = %s.\n", (*path)->dir);

	input = strdup(input_buffer);
	input = strtok(input, "\n");
	printf("get_path -> input_buffer = %s.\n", input_buffer);
	printf("get_path -> input = %s.\n", input);

	/* extrae el primer argumento de input */
	command = strtok(input_buffer, "\n");
	aux = strtok(command, " ");
	if (aux)
		command = aux;
	printf("get_path -> command = %s.\n", command);

	BLUE;
	/* check if the first argument is executable */	
	if (stat(command, &status) == 0) 
	{ 
		printf("get_path -> command executable.\n");
		return (command); 
	} 
	printf("get_path -> command NOT excutable.\n");
	RESET; 
 
	slash_command = concat("/", command);
	slash_input = concat("/", input);
	printf("get_path -> slash_command = %s.\n", slash_command);
	printf("get_path -> slash_input = %s.\n", slash_input);
	while (list_pointer) /* does not reach the end of the list */
	{
		/* check if command is executable in $list_pointer->dir */
		aux = concat(list_pointer->dir, slash_command);
		if (stat(aux, &status) == 0)
			break;
		// free(aux);
		list_pointer = list_pointer->next;
	}
	free(slash_command); 
	/* check if command is executable */
	if (stat(aux, &status) == 0)
	{
		BLUE;
		printf("get_path -> command: (%s) it's executable\n", aux);
		RESET;
		/* concatenar el resto de argumentos */
		free(aux);
		aux = concat(list_pointer->dir, slash_input);
		printf("get_path -> command to return:(%s)\n", aux);
		RED;
		printf("get_path -> clossing...\n");
		RESET;
		return (aux);
	}
	printf("get_path -> command: (%s) it's NOT executable\n", aux);
	printf("get_path -> command to return:(%s)\n", aux);
	free(aux);
	RED;
	printf("get_path -> clossing...\n");
	RESET;
	return (input);
}

/**
 * create_argv - turns input_buffer into argument vector.
 * @input_buffer: input_buffer to be processed.
 * Return: a pointer to the new argument vector.
 */
char **create_argv(char *input_buffer)
{
	int i = 0,  ac = 0, argc = 1;
	char *current_string, *str_to_put;
	char **argv;

	while (input_buffer[i])
	{
		/**
		 * counter increases if current position is a space
		 * and following position not NULL, space nor \n
		 */
		if (input_buffer[i] == ' ' &&
			(input_buffer[i + 1] &&
				(input_buffer[i + 1] != ' ' &&
					input_buffer[i + 1] != '\n')))
			argc += 1;
		i++;
	}

	argv = malloc(sizeof(char *) * (argc + 1));
	if (argv == NULL)
	{
		/* TODO print error */
		write(STDOUT_FILENO, "MALLOC ERROR\n", 14);
		return (NULL);
	}

	// TODO la func que busca el path no le quieta el \n antes de retornar?
	current_string = strtok(input_buffer, "\n");
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
