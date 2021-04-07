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

	GREEN;
	printf("|   ");
	BLUE;
	printf("start_shell runing...\n");
	RESET;
	while (1)
	{
		style1();
		GREEN;
		printf("baby_shell# ");
		// write(STDOUT_FILENO, "baby_shell# ", 12);
		RESET;
		getline(&input_buffer, &len, stdin);
		/* if buffer only contains spaces or the \n char will show prompt again */
		if (not_empty(input_buffer))
		{
			style1();
			printf("input_buffer not empty\n");
			input = create_argv(input_buffer, &path); // TODO change after compile -> input_buffer
			style1();
			printf("\n");

			/* // * temp condition to end program */
			if (!_strtwins(input[0], "exit"))
			{
				style1();
				BLUE;
				printf("exit condition detected\n");
				RESET;
				break;
			}
			style1();
			printf("fork\n");
			pid = fork();
			/* child process executes command, father process waits */
			if (pid == 0)
			{
				style1();
				printf("process %i executing command: (%s)\n", pid, input[0]);
				printf("=====================================================\n");
				if (execve(input[0], input, NULL) == -1)
				{
					write(STDOUT_FILENO, "No such file or directory\n", 27);
				}
				printf("=====================================================\n");
				break;
			}
			else
				wait(&status);
			printf("=====================================================\n");
			style1();
			printf("process %i cleaning temp input\n", pid);
			style1();
			printf("\n");
			style1();
			printf("\n");
			free_argv(input);
		}
	}
	style1();
	printf("process %i cleaning input\n", pid);
	free_argv(input);
	style1();
	printf("process %i cleaning input buffer\n", pid);
	free(input_buffer);
	RED;
	style1();
	printf("process %i clossing...\n", pid);
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
