#include "shell.h"

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
