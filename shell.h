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

#define BUFSIZE 1024

extern char **environ;

typedef struct info_s
{
	char **env;
	int status;
	char *name;
	int line_count;
} info_t;

ssize_t _getline(char **lineptr, size_t *n, int fd);

char *_strtok(char *str, const char *delim);
int is_delim(char c, const char *delim);

int _strlen(char *s);
char *_strcpy(char *dest, char *src);
int _strcmp(char *s1, char *s2);
char *_strdup(char *str);

char *_strcat(char *dest, char *src);
char *_strchr(char *s, char c);
int _atoi(char *s);
int _strncmp(char *s1, char *s2, int n);

char *_getenv(info_t *info, const char *name);
int init_env(info_t *info);
void free_env(info_t *info);

int check_builtin(info_t *info, char **args);
int shell_exit(info_t *info, char **args);
int shell_cd(info_t *info, char **args);
int shell_env(info_t *info, char **args);

int shell_setenv(info_t *info, char **args);
int _setenv(info_t *info, char *name, char *value);
int shell_unsetenv(info_t *info, char **args);
int _unsetenv(info_t *info, char *name);

int execute(info_t *info, char **args);
char *find_path(info_t *info, char *cmd);

void free_args(char **args);
char **split_line(char *line);

#endif
