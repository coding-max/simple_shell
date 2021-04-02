#include <stdarg.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(int ac, char **av)
{
	int i = 0;
	size_t len = 1024;
	char *buffer[1024];
	char *output;

	printf("$ ");
	getline(buffer, &len, stdin);
	output = strtok(*buffer, " ");
	fflush;
	while (output)
	{
		printf("%s \n", output);
		fflush;
		output = strtok(NULL, " ");
		fflush;
	}
	return (0);
}
