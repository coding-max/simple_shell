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
	char *input = NULL;

	while (1)
	{
		printf("baby_shell# ");
		getline(&input_buffer, &len, stdin);
		input = strtok(input_buffer, "\n");
		printf("%s\n", input);

		if (!strcmp(input, "exit"))
			break;
	}

	free(input_buffer);
	return (0);
}
