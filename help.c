#include "shell.h"

/**
 * print_help - Prints help for built-in commands
 * @name: Built-in name
 */
void print_help(char *name)
{
	if (name == NULL)
	{
		printf("help: help [BUILTIN]\n");
		printf("Built-ins: alias env exit help\n");
	}
	else if (strcmp(name, "alias") == 0)
		printf("alias: alias [name[='value'] ...]\n");
	else if (strcmp(name, "env") == 0)
		printf("env: env\n");
	else if (strcmp(name, "exit") == 0)
		printf("exit: exit\n");
	else if (strcmp(name, "help") == 0)
		printf("help: help [BUILTIN]\n");
}
