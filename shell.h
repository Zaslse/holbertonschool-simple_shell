#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>

#define BUFSIZE 1024

extern char **environ;

/**
 * struct info_s - Shell information struct
 * @name: Program name
 * @line: Input command line
 * @args: Command arguments
 * @env: Custom copy of environment
 * @status: Last exit status
 * @count: Execution count
 */
typedef struct info_s
{
	char *name;
	char *line;
	char **args;
	char **env;
	int status;
	int count;
} info_t;

int _strlen(const char *s);
char *_strcpy(char *dest, const char *src);
int _strcmp(const char *s1, const char *s2);
int _strncmp(const char *s1, const char *s2, size_t n);
char *_strdup(const char *str);
char *_strcat(char *dest, const char *src);
char *_strchr(const char *s, char c);
int _atoi(const char *s);
char *_itoa(int n);

void free_array(char **arr);

ssize_t _getline(char **lineptr, size_t *n, int fd);
char *_strtok(char *str, const char *delim);
char **tokenize(char *line);

int init_env(info_t *info);
void free_env(info_t *info);
char *_getenv(info_t *info, const char *name);
int _setenv(info_t *info, const char *name, const char *value);
int _unsetenv(info_t *info, const char *name);

int check_builtin(info_t *info);
int builtin_exit(info_t *info);
int builtin_env(info_t *info);
int builtin_setenv(info_t *info);
int builtin_unsetenv(info_t *info);
int builtin_cd(info_t *info);

char *find_path(info_t *info, char *cmd);
int execute(info_t *info);
void handle_comments(char *line);

void print_error(info_t *info, const char *msg);
void print_custom_error(info_t *info, const char *cmd, const char *msg);

#endif /* SHELL_H */
