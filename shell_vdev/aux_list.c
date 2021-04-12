#include "shell.h"

/**
 * list_path - create a list whith the direcories in the PATH.
 * @env: environment variable.
 * Return: a pointer to the new list.
 */
list_t *list_path(char **env)
{
	list_t *head = NULL;
	char **environ;
	int len, i;

	len = 0;
	while (env[len])
		len++;
	environ = malloc(sizeof(char *) * len);
	if (!environ)
	{
		perror("MALLOC");
		return (NULL);
	}

	i = 0;
	while (env[i])
	{
		environ[i] = str_dup(env[i]);
		i++;
	}

	head = create_list(environ);

	i = 0;
	while (i < len)
	{
		free(environ[i]);
		i++;
	}
	free(environ);

	return (head);
}


/**
 * create_list - create a list whith the direcories in the PATH.
 * @environ: environment variable.
 * Return: a pointer to the new list.
 */
list_t *create_list(char **environ)
{
	list_t *head = NULL, *temp = NULL;
	char *dir, *aux, *var_name, *var_value = NULL;
	int i;

	i = 0;
	while (environ[i])
	{
		var_name = strtok(environ[i], "=");
		if (str_twins(var_name, "PATH") == 0)
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
			dir = str_dup(aux);
			head = add_list(&head, dir);
			aux = strtok(NULL, ":");
		}
		temp = head;
		while (aux)
		{
			i++;
			dir = str_dup(aux);
			add_list(&head, dir);
			temp = temp->next;
			aux = strtok(NULL, ":");
		}
	}
	else
		perror("ERROR: var_value NULL\n");

	return (head);
}

/**
 * add_list - add a new node to the list.
 * @head: pointer to the list.
 * @dir: string to be placed in the new node.
 * Return: pointer to the list.
 */
list_t *add_list(list_t **head, char *dir)
{
	list_t *new, *aux = *head;

	new = malloc(sizeof(list_t));
	if (new == NULL)
	{
		perror("ERROR: unable to allocate memory\n");
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
