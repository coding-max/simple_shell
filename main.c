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

	if (!isatty(0))
	{
		/* reads stdin if arguments are passed with pipeline */
		getline(&stdin_buffer, &len, stdin);
		return (only_execute(stdin_buffer));
	}
	/* starts interactive shell */
	return (start_shell());
}
