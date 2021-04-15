<div align=center>  
    <img  
    style="text-align:center"  
    src="https://raw.githubusercontent.com/coding-max/hbtn_config/main/assets/hbtn_logo_low.png"  
    alt="Holberton School"/>  
    <h1 align="center"> Simple Shell </h1>  
</div>

**hsh** is a simple UNIX command interpreter that reads commands from standard input and executes them, simulating the behavior of the `sh`  (`/bin/sh`) command interpreter (shell).  
The program was written in C and is part of the low-level programming trak at [Holberton School](https://www.holbertonschool.com).  

> **hsh** is still under development and some functionalities contain errors, their status is indicated below.

## Use

### Compilation

The **hsh** was coded on an Ubuntu 14.04 LTS machine with gcc version 4.8.4.  
The code compile with `gcc -Wall -Werror -Wextra -pedantic *.c -o hsh` command.  

### Features

In interactive mode the **hsh** displays a prompt (hsh> ) and wait for the user to type a command.  
A command line always ends with a new line and the prompt is displayed again each time a command has been executed.  

|                                                                       |EXAMPLE                                     | STATUS
|-----------------------------------------------------------------------|--------------------------------------------|--------------------|
| Handles simple commands                                               |`/bin/ls`, `/usr/bin/pwd`                   | :white_check_mark: |
| Handles the `PATH`                                                    |`ls`, `pwd`, `whoami`                       | :on:               |
| Handles command lines with arguments                                  |`/bin/ls -las`, `ls -l /tmp`, `cat shell.h` | :white_check_mark: |
| Handles the `Ctrl + D` condition (end-of-file) to exit the program.   |                                            | :white_check_mark: |
| Handles the `Ctrl + C` signal to not kill the program.                |                                            | :white_check_mark: |
| Handles comments `(#)`                                                |`ls #-la /tmp`, `#pwd`                      | :white_check_mark: |
| Handles errors.                                                       |                                            | :on:               |
| Handles `help` buit-in command that prints information about builtin commands  | `help help`, `help exit`          | :white_check_mark: |
| Handles `exit` buit-in command that exits the shell                   | `exit`                                     | :on:               |
| Handles `env` buit-in command that prints the current environment     | `env`                                      | :on:               |

### Examples

The shell should work like this in interactive mode:  

```bash
coding-max@hbtn:~/simple_shell$ ./hsh
hsh>  ls
AUTHORS    built-ins.c  env-list.c  hsh     man_1_simple_shell  strings-1.c
README.md  dmemory.c    errors.c    main.c  shell.h             strings-2.c
hsh>  pwd
/home/coding-max/holberton/simple_shell
hsh>  exit
coding-max@hbtn:~/simple_shell$
```

The shell should work like this in non-interactive mode:  

```bash
coding-max@hbtn:~/simple_shell$ echo "/bin/ls" | ./hsh
AUTHORS    built-ins.c  env-list.c  hsh     man_1_simple_shell  strings-1.c
README.md  dmemory.c    errors.c    main.c  shell.h             strings-2.c
coding-max@hbtn:~/simple_shell$ echo "pwd" | ./hsh
/home/coding-max/holberton/simple_shell
coding-max@hbtn:~/simple_shell$
```

## Authors and License

[Maximiliano Pan](https://github.com/coding-max) & [Alina De Los Santos](https://github.com/alina-delossantos)  

This project is licensed under the MIT License - see the [LICENSE](https://github.com/coding-max/simple_shell/blob/main/LICENSE) file for details.
