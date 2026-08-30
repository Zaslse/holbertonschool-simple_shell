#include "shell.h"

/**
 * free_array - Frees a null-terminated array of strings
 * @arr: Array to free
 */
void free_array(char **arr)
{
	int i;

	if (arr == NULL)
		return;
	for (i = 0; arr[i] != NULL; i++)
	{
		free(arr[i]);
		arr[i] = NULL;
	}
	free(arr);
}
