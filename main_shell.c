#include "shell.h"

/**
 * start_shell - runs the interactive shell.
 * @env: environment variable.
 * Return: always 0 (success).
 */
int start_shell(void)
{
	size_t len = 0;
	char *input_buffer = NULL;
	char **input;
	int status;
	int pid = getpid();

	while (1)
	{
		write(STDOUT_FILENO, "baby_shell# ", 12);
		getline(&input_buffer, &len, stdin);
		/* if buffer only contains \n will show prompt again */
		if (!_strtwins(input_buffer, "\n"))
		/* TODO same applies when input are only spaces */
		{
			input = create_argv(input_buffer);

			/* // * temp condition to end program */
			if (_strtwins(input[0], "exit"))
				break;

			pid = fork();
			/* child process executes command, father process waits */
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

/**
 * only_execute - executes a command line.
 * @input_buffer: command line to execute.
 * Return: always 0 (success).
 */
int only_execute(char *input_buffer)
{
	char **input;
	int pid, status;

	input = create_argv(input_buffer);
	pid = fork();
	/* child process executes command, father process waits */
	if (pid == 0)
	{
		if (execve(input[0], input, NULL) == -1)
			write(STDOUT_FILENO, "No such file or directory\n", 27);
	}
	else
		wait(&status);

	free_argv(input);
	return (0);
}
