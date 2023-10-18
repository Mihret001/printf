#include "main.h"

/**
 * handle_print - for pringting an argument based on its type
 * @formatStr: a formatted string which is used to print the arguments.
 * @arg_list: List of arguments to be printed.
 * @ind: ind.
 * @outputBuffer: Buffer array to handle the formatted output.
 * @activeFlags: calculates active flags
 * @width: get the field width.
 * @precision: Precision specification
 * @size: Size specifier
 * Return: 1 or 2;
 */

int handle_print(const char *formatStr, int *ind, va_list arg_list,
	char outputBuffer[], int activeFlags,
	int width, int precision, int size)
{
	int l, unknow_len = 0, printed_chars = -1;
	formatStr_t formatStr_argList[] = {
		{'c', printFormattedCharacter}, {'s', printFormattedString},
		{'%', printFormattedPercentSign},
		{'i', printFormattedInteger}, {'d', printFormattedInteger},
		{'b', printFormattedBinary},
		{'u', printFormattedUnsigned}, {'o', printFormattedOctal},
		{'x', printFormattedHexadecimal}, {'X', printFormattedHexaUpper},
		{'p', printFormattedPointer}, {'S', print_NonPrintable},
		{'r', print_rev}, {'R', print_rot13str}, {'\0', NULL}
	};
	for (l = 0; formatStr_argList[l].formatStr != '\0'; l++)
		if (formatStr[*ind] == formatStr_argList[l].formatStr)
			return (formatStr_argList[l].fn(arg_list, outputBuffer,
					activeFlags, width, precision, size));

	if (formatStr_argList[l].formatStr == '\0')
	{
		if (formatStr[*ind] == '\0')
			return (-1);
		unknow_len += write(1, "%%", 1);
		if (formatStr[*ind - 1] == ' ')
			unknow_len += write(1, " ", 1);
		else if (width)
		{
			--(*ind);
			while (formatStr[*ind] != ' ' && formatStr[*ind] != '%')
				--(*ind);
			if (formatStr[*ind] == ' ')
				--(*ind);
			return (1);
		}
		unknow_len += write(1, &formatStr[*ind], 1);
		return (unknow_len);
	}
	return (printed_chars);
}
