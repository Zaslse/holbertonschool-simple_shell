#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>

extern char **environ;

int execute_cmd(char **argv, char *line);
void print_env(void);
int handle_alias(char *input);

#endif /* SHELL_H */
