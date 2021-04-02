#include <unistd.h>
#include <stdarg.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>


char *_getenv(const char *name);

/**
 * main - prints the environment
 *
 * Return: Always 0.
 */
int main(int ac, char **av, char **env)
{
    unsigned int i = 0;
    extern char **environ;

    while (env[i] != NULL)
    {
        printf("%s\n", env[i]);
        i++;
    }

    printf("\n-------------------------------------------------------\n\n");
    printf("Directories in the PATH: %s\n", _getenv("PATH"));
/*
    i = 0;
    while (environ[i] != NULL)
    {
        printf("%s\n", environ[i]);
        i++;
    }
*/

    return (0);
}

char *_getenv(const char *name)
{
    extern char **environ;
    int i = 0;
    char *output, *to_print, *buffer_to_print;

    while (environ[i] != NULL)
    {
        output = strtok(environ[i], "=");
        if (strcmp(output, name) == 0)
        {
           buffer_to_print = strtok(NULL, "\n");
           break;
        }
        i++;
    }
    to_print = strtok(buffer_to_print, "/");
    printf("%s\n", to_print);
    while (to_print)
	{
		printf("%s\n", to_print);
		fflush;
		to_print = strtok(NULL, "/");
		fflush;
	}
    
    return (buffer_to_print);
}
