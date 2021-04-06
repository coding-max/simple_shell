#include "shell.h"

/**
 * main - execute the interactive or non-interactive mode of the shell.
 * @ac: argument count.
 * @av: argument vector.
 * @env: environment variable.
 * Return: always 0 (success).
 */
int main(void)
{
	size_t len = 0;
	char *stdin_buffer = NULL;
	list_t *path;
	int aux;

	GREEN;
	printf("\nmain running...\n");
	RESET;
	path = list_path();
	if (0)
	{
		free_list(path);
		return (0);
	}
	if (!isatty(0))
	{
		/* reads stdin if arguments are passed with pipeline */
		getline(&stdin_buffer, &len, stdin);

		return (only_execute(stdin_buffer, path));
	}
	/* starts interactive shell */
	aux = start_shell(path);
	free_list(path);
	RED;
	printf("main clossing...\n");
	RESET;
	return (aux);
}
