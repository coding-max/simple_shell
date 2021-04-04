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
	char **input;
	int status, i = 0;
	int pid = getpid();

	while (1)
	{
		write(STDOUT_FILENO, "baby_shell# ", 12);
		getline(&input_buffer, &len, stdin);
		if (!_strtwins(input_buffer, "\n"))
		{
			//* test
			printf("\nstrat_shell runing...\n");
			printf("start_shell -> getline = %s\n", input_buffer);
			input = _strtoargv(input_buffer);

			//*  checks correct output of argv input
			printf("\nstrat_shell runing...\n");
			i = 0;
			while (input[i])
			{
				printf("strat_shell -> argv[%i] = %s\n", i, input[i]);
				i++;
			}
			printf("strat_shell -> argv[%i] = %s\n", i, input[i]);

			printf("temp.... before \"exit\" i=%i\n", i);
			
			if (_strtwins(input[0], "exit"))
			{
				printf("strat_shell -> process %i exit loop\n", pid);
				break;
			}
			
			printf("temp.... after \"exit\"\n");
			printf("strat_shell -> fork\n");
			pid = fork();
			if (pid == 0)
			{
				if (execve(input[0], input, NULL) == -1)
					write(STDOUT_FILENO, "No such file or directory\n", 27);
				printf("strat_shell -> process %i exit loop\n", pid);
				break;
			}
			else
				wait(&status);

			// TODO auxiliar function (clean_argv)
			i = 0;
			while(input[i])
			{
				free(input[i]);
				i++;
			}
			free(input);

		}
	}

	i = 0;
	while(input[i])
	{
		free(input[i]);
		i++;
	}
	free(input);
	free(input_buffer);

	printf("strat_shell -> process %i closed...\n", pid);
	return (0);
}

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
