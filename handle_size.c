#include "main.h"

/**
 * handle_size - calculates size to cast the argument
 * @formatStr: a formatted string which is used to print the arguments
 * @l: List of arguments to be printed.
 * Return: Size
 */

int handle_size(const char *formatStr, int *l)
{
	int curr_l = *l + 1;
	int size = 0;

	if (formatStr[curr_l] == 'l')
		size = S_LONG;
	else if (formatStr[curr_l] == 'h')
		size = S_SHORT;

	if (size == 0)
		*l = curr_l - 1;
	else
		*l = curr_l;

	return (size);
}
