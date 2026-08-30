#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>

extern char **environ;

int execute_cmd(char **argv, char *line, char *command, int count);
void print_env(void);
int handle_alias(char *input);
char *find_alias(char *name, int *index);
void free_aliases(void);
char *expand_variables(char *input, int status);
char *find_command_path(char *command);
void remove_comment(char *line);
void print_help(char *name);
void history_init(void);
void history_add(char *line);
void history_print(void);
void history_save(void);
void history_free(void);
int read_file_line(int fd, char **line, size_t *size);

#endif /* SHELL_H */
