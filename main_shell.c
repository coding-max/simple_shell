#include "shell.h"

/**
 * start_shell - runs the interactive shell.
 * @env: environment variable.
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
		printf("\nstart_shell runing...\n");
		write(STDOUT_FILENO, "baby_shell# ", 12);
		getline(&input_buffer, &len, stdin);
		/* if buffer only contains spaces or the \n char will show prompt again */
		printf("start_shell -> input_buffer = %s.\n", input_buffer);
		if (not_empty(input_buffer))
		{
			printf("start_shell -> input_buffer not empty\n");
			input_buffer_with_path = get_path(input_buffer, &path);

			printf("\nstart_shell runing...\n");
			printf("start_shell -> input_buffer_with_path = %s.\n", input_buffer_with_path);
			input = create_argv(input_buffer_with_path); // TODO change after compile -> input_buffer

			free(input_buffer_with_path);
			printf("\nstart_shell runing...\n");
			printf("start_shell -> input:\n");

			while (input[i])
			{
				printf("     [%i] = %s.\n", i, input[i]);
				i++;
			}

			/* // * temp condition to end program */
			if (!_strtwins(input[0], "exit"))
				break;

			printf("start_shell -> fork\n");
			pid = fork();
			/* child process executes command, father process waits */
			if (pid == 0)
			{
				printf("start_shell -> process %i executing (%s)\n", pid, input[0]);
				BLUE;
				if (execve(input[0], input, NULL) == -1)
					write(STDOUT_FILENO, "No such file or directory\n", 27);
				break;
			}
			else
				wait(&status);

			printf("start_shell -> process %i cleaning input\n", pid);
			free_argv(input);
		}
	}

	RESET;
	printf("start_shell -> process %i cleaning input\n", pid);
	free_argv(input);
	printf("start_shell -> process %i cleaning input buffer\n", pid);
	free(input_buffer);
	RED;
	printf("start_shell -> process %i clossing...\n", pid);
	RESET;
	return (0);
}

/**
 * only_execute - executes a command line.
 * @input_buffer: command line to execute.
 * Return: always 0 (success).
 */
int only_execute(char *input_buffer, list_t *path)
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
