#include "shell.h"

/**
 * start_shell - runs the interactive shell.
 * @path: pointer to the list of dir of the PATH.
 * Return: always 0 (success).
 */
int start_shell(list_t *path)
{
	size_t len = 0;
	char *input_buffer = NULL;
	char *input_buffer_with_path;
	char **input;
	int status;
	int pid = getpid(), i = 0;

	while (1)
	{
		write(STDOUT_FILENO, "baby_shell# ", 12);
		getline(&input_buffer, &len, stdin);
		/* if buffer only contains spaces or the \n char will show prompt again */
		if (not_empty(input_buffer))
		{
			input = create_argv(input_buffer, &path);

			/* // * temp condition to end program */
			if (!_strtwins(input[0], "exit"))
			{
				break;
			}
			pid = fork();
			/* child process executes command, father process waits */
			if (pid == 0)
			{
				if (execve(input[0], input, NULL) == -1)
				{
					write(STDOUT_FILENO, "No such file or directory\n", 27);
				}
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

/*// TODO handle the PATH on non-int mode */
/**
 * only_execute - executes a command line.
 * @input_buffer: command line to execute.
 * @path: pointer to the list of dir of the PATH.
 * Return: always 0 (success).
 */
int only_execute(char *input_buffer, list_t *path)
{
	char **input;
	int pid, status;

	input = create_argv(input_buffer, &path);
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
