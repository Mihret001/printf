#include "main.h"

void print_buffer(char outputBuffer[], int *buff_ind);

/**
 * _printf - serves as a printf function
 * @formatStr: format.
 * Return: Printed chars.
 */

int _printf(const char *formatStr, ...)
{
	int l, printed = 0, printed_chars = 0;
	int activeFlags, width, precision, size, buff_ind = 0;
	va_list arg_list;
	char outputBuffer[BUFF_SIZE];

	if (formatStr == NULL)
		return (-1);

	va_start(arg_list, formatStr);

	for (l = 0; formatStr && formatStr[l] != '\0'; l++)
	{
		if (formatStr[l] != '%')
		{
			outputBuffer[buff_ind++] = formatStr[l];
			if (buff_ind == BUFF_SIZE)
				print_buffer(outputBuffer, &buff_ind);
			/* write(1, &formatStr[l], 1);*/
			printed_chars++;
		}
		else
		{
			print_buffer(outputBuffer, &buff_ind);
			activeFlags = handle_flags(formatStr, &l);
			width = handle_width(formatStr, &l, arg_list);
			precision = handle_precision(formatStr, &l, arg_list);
			size = handle_size(formatStr, &l);
			++l;
			printed = handle_print(formatStr, &l, arg_list, outputBuffer,
				activeFlags, width, precision, size);
			if (printed == -1)
				return (-1);
			printed_chars += printed;
		}
	}

	print_buffer(outputBuffer, &buff_ind);

	va_end(arg_list);

	return (printed_chars);
}

/**
 * print_buffer - Prints the contents of buffer
 * @outputBuffer: an array of chars
 * @buff_ind: Index that represents the length.
 */
void print_buffer(char outputBuffer[], int *buff_ind)
{
	if (*buff_ind > 0)
		write(1, &outputBuffer[0], *buff_ind);

	*buff_ind = 0;
}
