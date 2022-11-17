## KSHS~$_SHELL

### Learning Objectives
> The goat of this project is to understand;
* How a shell works
* What a pid and a ppid is
* How to manipulate the environment of the current process
* What the difference between a function and a system call is
* How to create a process
* What the three prototypes of main are
* How a  shell uses the PATH to find programs
* How to execute another program with the execve system call
* How to suspend the execution of a process until one of its children terminates
* What EOF is / "end-of-file" means.

### Synopsis
> This repository contains functions that runs the "KSHS~$_SHELL" simple-shell
> This simplle shell handles the commands found the PATH directory with or without their respective paths
> The shell also runs some builtin functions described below e.g. ```cd```

### Builtins
* ```exit``` built-in, that exits the shell
* ```env``` built-in, that prints the current environment
* ```setenv``` built-in Initialize a new environment variable, or modify an existing one
* ```unsetenv``` built-in removes an envrionmental variable
* ```cd``` changes directory
* ```alias``` Prints a list of all aliases, one per line, in the form name='value'

### Some of the system calls used
```read```, ```write```, ```signal```, ```stat```, ```malloc```, ```free```, ```getcwd```, ```chdir```, ```execve```, ```wait```, ```exit```

### Compilation
* Style guidelines: [Betty style](https://github.com/holbertonschool/Betty/wiki)
```
#cisfun$ gcc -Wall -Werror -Wextra -pedantic -std=gnu89 *.c -o hsh
#cisfun$ ./hsh
KSHS~$
```
## Testing
Non-Interactive Mode
```
#csifun$ echo "ls -l" | ./hsh
hsh main.c shell.c test_ls_2
#cisfun$
#cisfun cat test_ls_2
/bin/ls
/bin/ls
#cisfun$
#cisfun$ cat test_ls_2 | ./hsh
hsh main.c shell.c test_ls_2
hsh main.c shell.c test_ls_2
#cisfun$
```
Interactive Mode

```
#cisfun$ ./hsh
KSHS~$ /bin/ls
hsh main.c shell.c
KSHS~$
KSHS~$ exit
#cisfun$
```
Sample Usage
```
KSK~$ ls -al
total 4
-rw-rw-r-- 1 vagrant vagrant   234 Mar 28 19:32 file1.c
-rw-rw-r-- 1 vagrant vagrant    69 Mar 28 19:32 file2.c
KSK~$ echo "This is a pretty cool!"
This is pretty cool!
KSHS~$ man ./man_1_simple_shell (opens our manpage for more information)
```
Stop and return to your original shell
```
KSHS~$ exit
#cisfun$
```


### Authors
youngspeculator & davislenny
