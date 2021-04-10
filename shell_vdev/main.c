#include "shell.h"

/**
 * main - execute the interactive or non-interactive mode of the shell.
 * @ac:argumen count (unused).
 * @av:argument vector (unused).
 * @env: environment variable.
 * Return: always 0 (success).
 */
int main(__attribute__((unused)) int ac,
		__attribute__((unused)) char **av, char **env)
{
	size_t len = 0;
	list_t *path;
	char *stdin_buffer = NULL;
	int aux;

	path = list_path(env);
	if (!isatty(0))
	{
		/* reads stdin if arguments are passed with pipeline */
		getline(&stdin_buffer, &len, stdin);
		aux = only_execute(stdin_buffer, path);
		free_list(path);
		free(stdin_buffer);
		return (aux);
	}
	/* starts interactive shell */
	aux = start_shell(path);
	free_list(path);
	return (aux);
}
