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
	printf("\n|   ");
	BLUE;
	printf("list_path runnig...\n");
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
		i = 0;
		aux = strtok(var_value, ":");
		if (aux)
		{
			dir = strdup(aux);
			head = add_to_list(&head, dir);
			style1();
			printf("%p -> dir[%i] = %s\n", &head->dir, i, head->dir);
			aux = strtok(NULL, ":");
		}
		temp = head;
		while (aux)
		{
			i++;
			dir = strdup(aux);
			node = add_to_list(&head, dir);
			temp = temp->next;
			style1();
			printf("%p -> dir[%i] = %s\n", &temp->dir, i, temp->dir);
			aux = strtok(NULL, ":");
		}
		/* TODO añadir ultimo dir en PATH */
	}
	else
	printf("     list_path -> ERROR: var_value NULL\n");
	GREEN;
	printf("|   ");
	BLUE;
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
}