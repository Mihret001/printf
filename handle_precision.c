#include "main.h"

/**
 * handle_precision - a function that calculates the precision for printing
 * @formatStr: a formatted string which is used to print the arguments
 * @l: the list of arguments to be printed.
 * @arg_list: list of arguments.
 * Return: the precision.
 */

int handle_precision(const char *formatStr, int *l, va_list arg_list)
{
	int curr_l = *l + 1;
	int precision = -1;

	if (formatStr[curr_l] != '.')
		return (precision);

	precision = 0;

	for (curr_l += 1; formatStr[curr_l] != '\0'; curr_l++)
	{
		if (is_digit(formatStr[curr_l]))
		{
			precision *= 10;
			precision += formatStr[curr_l] - '0';
		}
		else if (formatStr[curr_l] == '*')
		{
			curr_l++;
			precision = va_arg(arg_list, int);
			break;
		}
		else
			break;
	}

	*l = curr_l - 1;

	return (precision);
}
