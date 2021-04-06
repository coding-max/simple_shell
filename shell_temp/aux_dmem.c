#include "shell.h"

/**
* list_path - 
*/
list_t *list_path(void)
{
	list_t *head = NULL, *node = NULL, *temp = NULL;
	extern char **environ;
	char *var_name = NULL;
	char *var_value = NULL;
	char *dir, *aux;
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

	if (var_value)
	{
		aux = strtok(var_value, ":");
		if (aux)
		{
			dir = strdup(aux);
			head = add_to_list(&head, dir);
			printf("     list_path -> %p - temp->dir = %s\n", &head->dir, head->dir);
			aux = strtok(NULL, ":");
		}
		temp = head;
		while (aux)
		{
			dir = strdup(aux);
			node = add_to_list(&head, dir);
			temp = temp->next;
			printf("     list_path -> %p - temp->dir = %s\n", &temp->dir, temp->dir);
			aux = strtok(NULL, ":");
		}
		/* TODO añadir ultimo dir en PATH */
	}
	else
	printf("     list_path -> ERROR: var_value NULL\n");
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
			free(actual_node->dir);
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
	printf("     get_path -> path = %s.\n", (*path)->dir);

	input = strdup(input_buffer);
	input = strtok(input, "\n");
	printf("     get_path -> input_buffer = %s.\n", input_buffer);
	printf("     get_path -> input = %s.\n", input);

	/* extrae el primer argumento de input */
	command = strtok(input_buffer, "\n");
	aux = strtok(command, " ");
	if (aux)
		command = aux;
	printf("     get_path -> command = %s.\n", command);

	BLUE;
	/* check if the first argument is executable */	
	if (stat(command, &status) == 0) 
	{ 
		printf("     get_path -> command executable.\n");
		free(input);
		return (command); 
	} 
	printf("     get_path -> command NOT excutable.\n");
	RESET; 
 
	slash_command = concat("/", command);
	slash_input = concat("/", input);
	printf("     get_path -> slash_command = %s.\n", slash_command);
	printf("     get_path -> slash_input = %s.\n", slash_input);
	while (list_pointer) /* does not reach the end of the list */
	{
		/* check if command is executable in $list_pointer->dir */
		aux = concat(list_pointer->dir, slash_command);
		if (stat(aux, &status) == 0)
			break;
		// free(aux);
		list_pointer = list_pointer->next;
	}
	/* check if command is executable */
	if (stat(aux, &status) == 0)
	{
		BLUE;
		printf("     get_path -> command: (%s) it's executable\n", aux);
		RESET;
		/* concatenar el resto de argumentos */
		free(aux);
		aux = concat(list_pointer->dir, slash_input);
		printf("     get_path -> command to return:(%s)\n", aux);
		RED;
		printf("     get_path -> clossing...\n");
		RESET;
		free(input);
		free(slash_input);
		free(slash_command); 
		return (aux);
	}
	printf("     get_path -> command: (%s) it's NOT executable\n", aux);
	printf("     get_path -> command to return:(%s)\n", aux);
	free(aux);
	free(slash_input);
	free(slash_command); 
	RED;
	printf("get_path -> clossing...\n\n");
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

	new_input = input_buffer; // get_path(input_buffer, path);

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
