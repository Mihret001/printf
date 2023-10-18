#include "main.h"

/**
 * handle_width - a function calculating the width for printing
 * @formatStr: a formatted string which is used to print the arguments.
 * @l: the list of arguments to be printed.
 * @arg_list: list of arguments.
 * Return: width.
 */

int handle_width(const char *formatStr, int *l, va_list arg_list)
{
	int curr_l;
	int width = 0;

	for (curr_l = *l + 1; formatStr[curr_l] != '\0'; curr_l++)
	{
		if (is_digit(formatStr[curr_l]))
		{
			width *= 10;
			width += formatStr[curr_l] - '0';
		}
		else if (formatStr[curr_l] == '*')
		{
			curr_l++;
			width = va_arg(arg_list, int);
			break;
		}
		else
			break;
	}

	*l = curr_l - 1;

	return (width);
}
