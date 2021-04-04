#include "shell.h"

// TODO add comments
/**
 * start_shell - idk.
 * @env: environment variable.
 * Return: always 0 (success).
 */
int start_shell(char **env)
{
	size_t len = 0;
	char *input_buffer = NULL;
	char **input;
	int status, i = 0;
	int pid = getpid();

	while (1)
	{
		write(STDOUT_FILENO, "baby_shell# ", 12);
		getline(&input_buffer, &len, stdin);
		if (!_strtwins(input_buffer, "\n"))
		{
			input = create_argv(input_buffer);

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

			free_argv(input);
		}
	}

	free_argv(input);
	free(input_buffer);
	return (0);
}

// TODO handle command lines with arguments
/**
 * only_execute - idk.
 * @input_buffer: program to execute.
 * Return: always 0 (success).
 */
int only_execute(char *input_buffer)
{
	char *input[] = {input_buffer, NULL};
	int pid, status;

	pid = fork();
	if (pid == 0)
	{
		if (execve(input[0], input, NULL) == -1)
			write(STDOUT_FILENO, "No such file or directory\n", 27);
	}
	else
		wait(&status);

	return (0);
}
