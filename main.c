#include "shell.h"

/**
 * main - execute the interactive or non-interactive mode of the shell.
 * @ac:argumen count (unused).
 * @av:argument vector (unused).
 * @env: environment variable.
 * Return: always 0 (success).
 */
int main(__attribute__((unused)) int ac,
		__attribute__((unused)) char **av, char **env)
{
	size_t len = 0;
	list_t *path;
	char *stdin_buffer = NULL;
	int aux;

	signal(SIGINT, SIG_IGN);
	path = list_path(env);
	if (!isatty(0))
	{
		/* reads stdin if arguments are passed with pipeline */
		getline(&stdin_buffer, &len, stdin);
		aux = execute_buffer(stdin_buffer, path, env);
		free_list(path);
		free(stdin_buffer);
		return (aux);
	}
	/* starts interactive shell */
	aux = start_shell(path, env);
	free_list(path);
	return (aux);
}

/**
 * start_shell - runs the interactive shell.
 * @path: pointer to the list of dir of the PATH.
 * @env: environment variable.
 * Return: always 0 (success).
 */
int start_shell(list_t *path, char **env)
{
	char *buffer = NULL;
	int status;
	size_t len = 0;

	while (1)
	{
		write(STDOUT_FILENO, "\033[0;36mhsh# \033[0m", 16);
		signal(SIGINT, ctrl_c);
		status = getline(&buffer, &len, stdin);
		if (status == -1)
		{
			perror("CTRL+D");
			free(buffer);
			break;
		}
		/* if buffer only contains spaces or the \n char will show prompt again */
		status = execute_buffer(buffer, path, env);
		if (status == -1 || status == 1 || status == 2)
		{
			if (status == -1)
				perror("COMMAND NOT FOUND");
			free(buffer);
			break;
		}
	}
	return (status);
}

/**
 * execute_buffer - executes a command line.
 * @buffer: command line to execute.
 * @path: pointer to the list of dir of the PATH.
 * @env: environment variable.
 * Return: always 0 (success).
 */
int execute_buffer(char *buffer, list_t *path, char **env)
{
	char *buffer_tr, *input_buffer, *new_buffer;
	int aux, final, exe_result = 0;

	buffer_tr = clean_comments(buffer);
	input_buffer = str_tr(buffer_tr, '\t', ' ');
	if (not_empty(input_buffer))
	{
		final = str_count(input_buffer);
		if (final > 1)
		{
			aux = check_syntax(input_buffer);
			if (aux == -1)
			{
				print_error(input_buffer, 2);
				free(input_buffer);
				return (-1);
			}
			new_buffer = str_tr(input_buffer, ';', '\n');
		}
		else
			new_buffer = str_dup(input_buffer);

		exe_result = execute_command(new_buffer, path, env, final);
		free(new_buffer);
	}
	free(input_buffer);
	free(buffer_tr);
	return (exe_result);
}

/**
 * execute_command - run a command.
 * @new_buffer: command line to execute.
 * @path: pointer to the list of dir of the PATH.
 * @env: environment variable.
 * @final: total number of separate commands (;).
 * Return: 0 (successful), 1 (command not found), or 2 (exit command).
 */
int execute_command(char *new_buffer, list_t *path, char **env, int final)
{
	char *tmp_buffer, *current_buffer;
	char **input;
	int i, aux, current, status, exe_result = 0;
	pid_t pid = getpid();

	current = 0;
	while (current < final)
	{
		tmp_buffer = str_dup(new_buffer);
		current_buffer = strtok(tmp_buffer, "\n");
		for (i = 0; i < current; i++)
			current_buffer = strtok(NULL, "\n");
		input = create_argv(current_buffer, &path);
		/* // * temp condition to end program */
		aux = builtins(input, env);
		if (aux == 2)
		{
			free(tmp_buffer);
			return (2);
		}
		if (aux == 0)
		{
			pid = fork();
			/* child process executes command, father process waits */
			if (pid == 0)
			{
				if (execve(input[0], input, NULL) == -1)
				{
					print_error(input[0], 1);
					exe_result = 1;
				}
			}
			else
				wait(&status);
		}
		free_argv(input);
		free(tmp_buffer);
		current++;
	}
	return (exe_result);
}
