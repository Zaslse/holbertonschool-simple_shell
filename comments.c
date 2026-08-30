#include "shell.h"

/**
 * remove_comment - Removes comments from input
 * @line: Input line
 */
void remove_comment(char *line)
{
	int i;

	for (i = 0; line[i] != '\0'; i++)
	{
		if (line[i] == '#' &&
		    (i == 0 || line[i - 1] == ' ' || line[i - 1] == '\t'))
		{
			line[i] = '\0';
			break;
		}
	}
}
