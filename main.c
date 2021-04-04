#include "shell.h"

// TODO update flowchart
/**
 * main - exacute the interactive or non-interactive mode of the shell.
 * @ac: argument count.
 * @av: argument vector.
 * @env: environment variable.
 * Return: always 0 (success).
 */
int main(int ac, char **av, char **env)
{
	size_t len = 0;
	char *stdin_buffer = NULL;
	// char *input_buffer = NULL;

	if (!isatty(0))
	{
		/* reads stdin if arguments are passed with pipeline */
		getline(&stdin_buffer, &len, stdin);
		// input_buffer = strtok(stdin_buffer, "\n");
		return (only_execute(stdin_buffer));
	}
	/* strat interactive shell */
	return (start_shell(env));
}
