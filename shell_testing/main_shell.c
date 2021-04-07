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


	open_start_shell();
	while (1)
	{
		prompt(); // write(STDOUT_FILENO, "baby_shell# ", 12);
		getline(&input_buffer, &len, stdin);
		/* if buffer only contains spaces or the \n char will show prompt again */
		if (not_empty(input_buffer))
		{
			debug_1_shell();
			input = create_argv(input_buffer, &path);
			debug_2_shell();

			/* // * temp condition to end program */
			if (!_strtwins(input[0], "exit"))
			{
				debug_3_shell();
				break;
			}
			debug_4_shell();
			pid = fork();
			/* child process executes command, father process waits */
			if (pid == 0)
			{
				debug_5_shell(pid, input[0]);
				if (execve(input[0], input, NULL) == -1)
				{
					write(STDOUT_FILENO, "No such file or directory\n", 27);
				}
				debug_6_shell();
				break;
			}
			else
				wait(&status);
			debug_7_shell(pid);
			free_argv(input);
		}
	}
	debug_8_shell(pid);
	free_argv(input);
	debug_9_shell(pid);
	free(input_buffer);
	close_start_shell(pid);
	return (0);
}

// TODO handle the PATH on non-int mode
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
