#include "shell.h"

/**
 * list_path - create a list whith the direcories in the PATH.
 * @environ: environment variable.
 * Return: a pointer to the new list.
 */
list_t *list_path(char **environ)
{
	list_t *head = NULL, *temp = NULL;
	char *var_name = NULL, *var_value = NULL;
	char *dir, *aux;
	int i = 0;

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
			dir = _strdup(aux);
			head = add_to_list(&head, dir);
			aux = strtok(NULL, ":");
		}
		temp = head;
		while (aux)
		{
			i++;
			dir = _strdup(aux);
			add_to_list(&head, dir);
			temp = temp->next;
			aux = strtok(NULL, ":");
		}
	}
	else
		printf("ERROR: var_value NULL\n");

	return (head);
}

/**
 * add_to_list - add a new node to the list.
 * @head: pointer to the list.
 * @dir: string to be placed in the new node.
 * Return: pointer to the list.
 */
list_t *add_to_list(list_t **head, char *dir)
{
	list_t *new, *aux = *head;

	new = malloc(sizeof(list_t));
	if (new == NULL)
	{
		printf("ERROR: unable to allocate memory\n");
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
 * free_list - free the list of direcories.
 * @head: pinter to the list.
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
