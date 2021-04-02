#include <stdarg.h>
#include <stdlib.h>
#include <stdio.h>

int main(int ac, char **av)
{
	int i = 0;
	size_t len = 1024;
	char *buffer[1024];

	printf("$ ");
	getline( buffer, &len, stdin);
	printf("%s", *buffer);
	return (0);
}
