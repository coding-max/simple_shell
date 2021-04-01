#include <stdarg.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

/*
Write a program that executes the command ls -l /tmp in 5 different child processes. 
Each child should be created by the same process (the father). 
Wait for a child to exit before creating a new child.
*/
int main(int ac, char **av)
{
    char *argv[] = {"/bin/ls", "-l", "/usr/", NULL};
	int ppid = getpid();
	int i, status;

	printf("PPID: %d, PID: %d - antes de los forks\n",  ppid, getpid());
	/* crear los 5 forks (solo lo hace el proceso padre) */
	for (i = 0; i < 5 && getpid() == ppid; i++)
	{
		if (getpid() == ppid)
			fork();
		if (getpid() == ppid)
			wait(&status);
	}
	printf("PPID: %d, PID: %d - despues de los forks\n",  ppid, getpid());
	/* ejecutar el programa ls (solo solo hacen los procesos hijos) */
	if (getpid() != ppid)
	{
		printf("ANTES DEL printf QUE NO ANDA\n");
		printf("PPID: %d, PID: %d\n",  ppid, getpid());
		printf("DESPUES DEL printf QUE NO ANDA\n");
    	if (execve(argv[0], argv, NULL) == -1)
    	{
        	perror("Error:");
    	}
		printf("\n\n");
	}
	return (0);
}
