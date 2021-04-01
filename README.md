<div align=center>
    <img style="height:70px;text-align:center" src="https://dl.dropboxusercontent.com/s/bfcg5nzqunl9q6c/Holberton.png?dl=0" alt="Holberton School"/>
    <h1 align="center">0x16. C - Simple Shell</h1>
</div>


### Allowed functions and system calls:

- getpid (man 2 getpid)  
`pid_t getpid(void)` returns the process ID (PID) of the calling process  

- getline (man 3 getline)  
`ssize_t getline(char **restrict lineptr, size_t *restrict n, FILE *restrict stream)` delimited string input.   
Return: On success the number of characters read, including the delimiter character, but not the ‘\0’, -1 on failure to read a line.  

- getcwd (man 3 getcwd)  
`char *getcwd(char *buf, size_t size)` get current working directory.  
Return: pointer to a string containing the pathname of the current working directory. On failure, these functions return NULL.  

- execve (man 2 execve)  
`int execve(const char *pathname, char *const argv[], char *const envp[])` executes the program referred to by pathname. This causes the program that is currently being run by the calling process to be replaced with a new program.    
Return: -1 error.  

- fork (man 2 fork)  
`pid_t fork(void)` creates a new process by duplicating the calling process.
The new process is referred to as the child process.  
Return: On success, the PID of the child process is returned in the parent, and 0 is returned in the child. On failure, -1 is returned in the parent.  

- wait (man 2 wait)  
`pid_t wait(int *wstatus)` wait for process to change state.  
Return: on success, returns the process ID of the terminated child; on failure, -1 is returned.  

    - waitpid (man 2 waitpid) - `pid_t waitpid(pid_t pid, int *wstatus, int options)`  
    - wait3 (man 2 wait3) - `pid_t wait3(int *status, int options, struct rusage *rusage)`  
    - wait4 (man 2 wait4) - `pid_t wait4(pid_t pid, int *status, int options, struct rusage *rusage)`  

- open (man 2 open)  
`int open(const char *pathname, int flags)` open and possibly create a file.  
Return: On success return the new file descriptor (a nonnegative integer).  -1 on error.  

- close (man 2 close)  
`int close(int fd)` closes a file descriptor.  
Return: 0 success, -1 error.  

- opendir (man 3 opendir)  
`DIR *opendir(const char *name)` open a directory.  
Return: a pointer to the directory stream.  On error, NULL is returned.  

- closedir (man 3 closedir)  
`int closedir(DIR *dirp)` the function closes the directory stream associated with dirp.  
Return: 0 success, -1 error.  

- chdir (man 2 chdir)  
`int chdir(const char *path)` changes the current working directory of the calling process to the directory specified in path.   
Return: 0 success, -1 error.  

- access (man 2 access)  
`int access(const char *pathname, int mode)` checks whether the calling process can access the file pathname. If pathname is a symbolic link, it is dereferenced.   
Return: 0 success, -1 error.  

- exit (man 3 exit)  
`noreturn void exit(int status)` cause normal process termination.  

- _exit (man 2 _exit)  
`noreturn void _exit(int status)`  terminates the calling process "immediately".  

- kill (man 2 kill)  
`int kill(pid_t pid, int sig)` can be used to send any signal to any process group or process. If pid is positive, then signal sig is sent to the process with the ID specified by pid. If pid equals 0, then sig is sent to every process in the process group of the calling process. If pid equals -1, then sig is sent to every process for which the calling process has permission to send signals, except for process 1 (init), but see below. If pid is less than -1, then sig is sent to every process in the process group whose ID is -pid.   
Return: 0 success, -1 error.  

- perror (man 3 perror)  
`void perror(const char *s)` print a system error message.  

- fflush (man 3 fflush)  
`int fflush(FILE *stream)` flush a stream.  
Return: 0 success, EOF error.  

- malloc (man 3 malloc)  
`void *malloc(size_t size)` allocate dynamic memory.  

- free (man 3 free)  
`void free(void *ptr)` free allocated memory.  

- readdir (man 3 readdir)  
`struct dirent *readdir(DIR *dirp)` returns a pointer to a dirent structure representing the next directory entry in the directory stream pointed to by dirp.  It returns NULL on reaching the end of the directory stream or if an error occurred.  
Return: On success, readdir() returns a pointer to a dirent structure. If an error occurs, NULL is returned.  

- read (man 2 read)  
`ssize_t read(int fd, void *buf, size_t count)` read from a file descriptor.  
Return: On success, the number of bytes read is returned (zero indicates end of file), On error, -1 is returned.  

- write (man 2 write)
`ssize_t write(int fd, const void *buf, size_t count)` writes up to count bytes from the buffer starting at buf to the file referred to by the file descriptor fd.  
Return: number of bytes written is returned.  On error, -1 is returned.  

- strtok (man 3 strtok)  
`char *strtok(char *restrict str, const char *restrict delim)` extract tokens from strings.  
Return: a pointer to the next token, or NULL if there are no more tokens.  

- isatty (man 3 isatty)  
`int isatty(int fd)` test whether a file descriptor refers to a terminal.  
Return: 1 if fd is an open file descriptor referring to a terminal; otherwise 0 is returned.  

- signal (man 2 signal)  

- stat (__xstat) (man 2 stat)  

- lstat (__lxstat) (man 2 lstat)  

- fstat (__fxstat) (man 2 fstat)  