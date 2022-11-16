#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>

/* for read/write buffers */
#define BUF_SIZE 1024
#define BUF_FLUSH -1

/* for command chaining */
#define CMD_NORM	0
#define CMD_OR		1
#define CMD_AND		2
#define CMD_CHAIN	3

/* for convert_number() */
#define CONVERT_LOWERCASE	1
#define CONVERT_UNSIGNED	2

/* 1 if using system getline() */
#define USE_GETLINE 0

#define HIST_MAX	4096/* minimum size a file or directory entry */
#define HIST_FILE	".simple_shell_history"

extern char **environ;/* access the environment */


/**
 * struct liststr - singly linked list
 * @num: the number field
 * @str: a string
 * @next: points to the next node
 */
typedef struct liststr
{
	int num;
	char *str;
	struct liststr *next;
} list_t;

/**
 * struct passinfo - contains pseudo-arguements to pass into a function,
 *		allowing uniform prototype for function pointer struct
 * @arg: a string generated from getline containing arguements
 * @argv: an array of strings generated from arg
 * @path: a string path for the current command
 * @argc: the argument count
 * @line_count: the error count
 * @err_num: the error code for exit()s
 * @linecount_flag: if on count this line of input
 * @fname: the program filename
 * @env: linked list local copy of environ
 * @environ: custom modified copy of environ from LL env
 * @history: the history node
 * @alias: the alias node
 * @env_changed: on if environ was changed
 * @status: the return status of the last exec'd command
 * @cmd_buf: address of pointer to cmd_buf, on if chaining
 * @cmd_buf_type: CMD_type ||, &&, ;
 * @readfd: the fd from which to read line input
 * @histcount: the history line number count
 */
typedef struct passinfo
{
	char *arg;
	char **argv;
	char *path;
	int argc;
	unsigned int line_count;
	int err_num;
	int linecount_flag;
	char *fname;
	list_t *env;
	list_t *history;
	list_t *alias;
	char **environ;
	int env_changed;
	int status;

	char **cmd_buf; /* pointer to cmd ; chain buffer, for memory management */
	int cmd_buf_type; /* CMD_type ||, &&, ; */
	int readfd;
	int histcount;
} info_t;

#define INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
	0, 0, 0}

/**
 *struct builtin - contains a builtin string and related function
 *@name: the builtin command name
 *@func: the function
 */
typedef struct builtin
{
	char *name;
	int (*func)(info_t *);
} builtin_t;


/* shell_loop.c */
int run_shell(info_t *, char **);
int get_builtin_func(info_t *);
void find_path_cmd(info_t *);
void hsh_execute(info_t *);

/* path_func.c */
int is_cmd(info_t *, char *);
char *dup_chars(char *, int, int);
char *find_path(info_t *, char *, char *);

/* error_func.c */
void _eputs(char *);
int _eputchar(char);
int _putfd(char c, int fd);
int _putsfd(char *str, int fd);

/* string_func.c */
int _strlen(char *);
int _strcmp(char *, char *);
char *starts_with(const char *, const char *);
char *_strcat(char *, char *);

/* string_func2.c */
char *_strcpy(char *, char *);
char *_strdup(const char *);
void _puts(char *);
int _putchar(char);
char **strtow(char *, char *);

/* string_func3.c */
char *_strncpy(char *, char *, int);
char *_strncat(char *, char *, int);
char *_strchr(char *, char);

/* memory_func.c */
char *_memset(char *, char, unsigned int);
void ffree(char **);
void *_realloc(void *, unsigned int, unsigned int);
int bfree(void **);

/* more_functions.c */
int interactive(info_t *);
int tok_delim(char, char *);

/* more_functions2.c */
int _erratoi(char *);
void print_error(info_t *, char *);
char *convert_number(long int, int, int);
void remove_comments(char *);

/* builtin_func.c */
int _myexit(info_t *);
int _mycd(info_t *);
int _myhelp(info_t *);

/* more_builtins.c */
int _myhistory(info_t *);
int unset_alias(info_t *, char *);
int set_alias(info_t *, char *);
int print_alias(list_t *);
int _myalias(info_t *);

/* input_buf.c */
ssize_t get_input(info_t *);
int _getline(info_t *, char **, size_t *);
void ctrl_C(int);

/* info_struct_func.c */
void clear_info(info_t *);
void set_info(info_t *, char **);
void free_info(info_t *, int);

/* env.c */
char *_getenv(info_t *, const char *);
int _myenv(info_t *);
int _mysetenv(info_t *);
int _myunsetenv(info_t *);
int populate_env_list(info_t *);

/* more_env.c */
char **get_environ(info_t *);
int _unsetenv(info_t *, char *);
int _setenv(info_t *, char *, char *);

/* hist_data.c */
char *get_history_file(info_t *info);
int write_history(info_t *info);
int read_history(info_t *info);
int build_history_list(info_t *info, char *buf, int linecount);
int renumber_history(info_t *info);

/* list_str.c module */
list_t *add_node(list_t **, const char *, int);
list_t *add_node_end(list_t **, const char *, int);
size_t print_list_str(const list_t *);
int delete_node_at_index(list_t **, unsigned int);
void free_list(list_t **);

/* list_strII.c */
size_t list_len(const list_t *);
char **list_to_strings(list_t *);
size_t print_list(const list_t *);
list_t *node_starts_with(list_t *, char *, char);
ssize_t get_node_index(list_t *, list_t *);

/* chain.c */
int is_chain(info_t *, char *, size_t *);
void check_chain(info_t *, char *, size_t *, size_t, size_t);
int replace_alias(info_t *);
int replace_vars(info_t *);
int replace_string(char **, char *);

#endif /* SHELL_H */
