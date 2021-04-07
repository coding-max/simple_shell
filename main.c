#include "shell.h"

/**
 * main - execute the interactive or non-interactive mode of the shell.
 * Return: always 0 (success).
 */
int main(void)
{
	size_t len = 0;
	list_t *path;
	char *stdin_buffer = NULL;
	int aux;

	path = list_path();
	if (!isatty(0))
	{
		/* reads stdin if arguments are passed with pipeline */
		getline(&stdin_buffer, &len, stdin);
		return (only_execute(stdin_buffer, path));
	}
	/* starts interactive shell */
	aux = start_shell(path);
	free_list(path);
	return (aux);
}
