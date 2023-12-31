#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <limits.h>
#include <errno.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/stat.h>

#define NORM 0
#define OR 1
#define AND 2
#define CHAIN 3

#define GETLINE 0
#define STRTOK 0

#define HIST_F ".simple_shell_history"
#define HIST_M 4096

#define BUFFER_FLUSH -1
#define WRITE_BUFFER_SIZE 1024
#define READ_BUFFER_SIZE 1024

#define UNSIGNED_CONVERT 2
#define LOWERCASE_CONVERT 1

extern char **environ;

/**
 * struct liststr - singly linked list
 * @num: number field
 * @str: string
 * @next: pointer to next node
 */
typedef struct liststr
{
	int num;
	char *str;
	struct liststr *next;
} lists;

/**
 *struct passinfo - contains pseudo-arguments to pass into a function,
 *					allowing uniform prototype for function pointer struct
 *@path: a string path for the current command
 *@arg: a string generated from getline containing arguements
 *@argc: the argument count
 *@argv: an array of strings generated from arg
 *@err_num: the error code for exit()s
 *@linecount_flag: if on count this line of input
 *@line_count: the error count
 *@fname: the program filename
 *@env: linked list local copy of environ
 *@alias: the alias node
 *@history: the history node
 *@environ: custom modified copy of environ from LL env
 *@status: the return status of the last exec'd command
 *@env_changed: on if environ was changed
 *@cmd_buf_type: CMD_type ||, &&, ;
 *@cmd_buf: address of pointer to cmd_buf, on if chaining
 *@readfd: the fd from which to read line input
 *@histcount: the history line number count
 */
typedef struct passinfo
{
	char *path;
	char *arg;
	int argc;
	char **argv;
	int err_num;
	int linecount_flag;
	unsigned int line_count;
	char *fname;
	lists *env;
	lists *alias;
	lists *history;
	char **environ;
	int status;
	int env_changed;

	int cmd_buf_type;
	char **cmd_buf;
	int readfd;
	int histcount;
} info;

#define INFO_INIT\
	{\
		NULL, NULL, 0, NULL, 0, 0, 0, NULL, NULL, NULL, \
			NULL, NULL, 0, 0, 0,\
			NULL, 0, 0\
	}

/**
 * struct builtin - contains builtin string and related function
 * @flag: command flag of builtin
 * @function: function
 */
typedef struct builtin
{
	char *flag;
	int (*function)(info *);
} builtin_t;

char *_starting_with(const char *haystack, const char *needle);
char *_strcat(char *destination, char *source);
int _strcmp(char *str1, char *str2);
int _strlen(char *str);
int _putchar(char c);
void _puts(char *s);
char *_strdup(const char *s);
char *_strcpy(char *destination, char *source);
char *_strncpy(char *destination, char *source, int n);
char *_strncat(char *destination, char *source, int n);
char *_strchr(char *str, char c);
char **strtow(char *str, char *del);
char **strtow2(char *str, char del);
char *_memset(char *memo_ptr, char bytes, unsigned int n);
void _free(char **ss);
void *_realloc(void *pointer, unsigned int old_size, unsigned int new_size);
int pfree(void **pointer);
int _interact(info *info);
int is_delimeter(char c, char *delimeter);
int _isalpha(int c);
int _atoi(char *str);
char *number_convert(long int number, int base, int flags);
int _erroratoi(char *str);
void rem_comments(char *buffer);
void print_err(info *info, char *err_str);
int print_decimal(int in_put, int fd);
int _errputchar(char c);
void _errputs(char *str);
int _putsfd(char *str, int fd);
int _putfd(char c, int fd);
lists *node_add(lists **head, const char *str, int num);
lists *node_end(lists **head, const char *str, int num);
size_t print_list(const lists *h);
int delete_node(lists **head, unsigned int index);
void free_list(lists **head_p);
void clear_information(info *info);
void set_information(info *info, char **av);
void free_information(info *info, int all);
size_t list_length(const lists *head);
char **ls_to_str(lists *h);
size_t print_ls(const lists *head);
lists *starting_with_node(lists *head_node, char *pre, char c);
ssize_t getting_node_idx(lists *h, lists *node);
ssize_t get_ip(info *info);
int _getline(info *info, char **ptr, ssize_t *length);
void sigintHandler(__attribute__((unused)) int sig_num);
int build_history(info *info, char *buf, int linecount);
void chain_check(info *information,
				 char *buffer, size_t *ap, size_t start, size_t length);
int is_chain(info *information, char *buffer, size_t *ap);
int alias_replace(info *information);
int string_replace(char **old_str, char *new_str);
int vars_replace(info *information);
char *get_history(info *info);
int history_write(info *info);
int history_read(info *info);
int renumber_history(info *info);
int current_env(info *information);
char *get_env(info *information, const char *var);
int myset_env(info *information);
int myunset_env(info *information);
int envlist_populating(info *information);
int unset_env(info *information, char *var);
int set_env(info *information, char *var, char *value);
char **print_environ(info *information);
int own_exit(info *information);
int own_cd(info *information);
int own_help(info *information);
int my_history(info *information);
int alias_unset(info *information, char *s);
int alias_set(info *information, char *s);
int alias_print(lists *n);
int own_alias(info *information);
int is_cmd(info *info, char *path);
char *dup_charct(char *pathstr, int start, int stop);
char *find_pathing(info *info, char *pathstr, char *cmd);
int main(int ac, char **av);
int hsh(info *information, char **av);
int builtin_find(info *information);
void command_find(info *information);
void command_fork(info *information);

#endif
