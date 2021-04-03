#include "shell.h"

/**
 * start_shell - idk.
 * @env: environment variable.
 * Return: always 0 (success).
 */
int start_shell(char **env)
{
	size_t len = 0;
	char *input_buffer = NULL;
	char *input[] = {"", NULL};
	int pid, status;

	while (1)
	{
		write(STDOUT_FILENO, "baby_shell# ", 12);
		getline(&input_buffer, &len, stdin);
		if (!_strtwins(input_buffer, "\n"))
		{
			input[0] = strtok(input_buffer, "\n");

			if (_strtwins(input[0], "exit"))
				break;

			pid = fork();
			if (pid == 0)
			{
    			if (execve(input[0], input, NULL) == -1)
				write(STDOUT_FILENO, "No such file or directory\n", 27);
				break;
			}
			else
				wait(&status);
		}
	}

	free(input_buffer);
	return (0);
}
