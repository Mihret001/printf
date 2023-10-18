#include "main.h"

/****************** PRINT FORMATTED POINTER ******************/
/**
 * printFormattedPointer - a function printing the value of a pointer variable
 * @argList: List of arguments
 * @outputBuffer: Buffer array to handle formatted ouput
 * @activeFlags: Calculates active flags
 * @width: get width
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Number of chars printed.
 */

int printFormattedPointer(va_list argList, char outputBuffer[],
	int activeFlags, int width, int precision, int size)
{
	char extra_ch = 0, padd = ' ';
	int ind = BUFF_SIZE - 2, length = 2, padd_start = 1; /* length=2, for '0x' */
	unsigned long numb_addrs;
	char mapTo[] = "0123456789abcdef";
	void *addrs = va_arg(argList, void *);

	UNUSED(width);
	UNUSED(size);

	if (addrs == NULL)
		return (write(1, "(nil)", 5));

	outputBuffer[BUFF_SIZE - 1] = '\0';
	UNUSED(precision);

	numb_addrs = (unsigned long)addrs;

	while (numb_addrs > 0)
	{
		outputBuffer[ind--] = mapTo[numb_addrs % 16];
		numb_addrs /= 16;
		length++;
	}

	if ((activeFlags & F_ZERO) && !(activeFlags & F_MINUS))
		padd = '0';
	if (activeFlags & F_PLUS)
		extra_ch = '+', length++;
	else if (activeFlags & F_SPACE)
		extra_ch = ' ', length++;

	ind++;

	/*return (write(1, &buffer[i], BUFF_SIZE - i - 1));*/
	return (write_pointer(outputBuffer, ind, length,
		width, activeFlags, padd, extra_ch, padd_start));
}

/************************* PRINT NON PRINTABLE *************************/
/**
 * print_NonPrintable - Prints ascii codes of non printable chars in hexadec
 * @argList: List of arguments
 * @outputBuffer: Buffer array to handle formatted output
 * @activeFlags: Calculates active flags
 * @width: get width
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Number of chars printed
 */

int print_NonPrintable(va_list argList, char outputBuffer[],
	int activeFlags, int width, int precision, int size)
{
	int i = 0, offset = 0;
	char *str = va_arg(argList, char *);

	UNUSED(activeFlags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);

	if (str == NULL)
		return (write(1, "(null)", 6));

	while (str[i] != '\0')
	{
		if (is_printable(str[i]))
			outputBuffer[i + offset] = str[i];
		else
			offset += append_hexaDeCode(str[i], outputBuffer, i + offset);

		i++;
	}

	outputBuffer[i + offset] = '\0';

	return (write(1, outputBuffer, i + offset));
}

/************************* PRINT REVERSE *************************/
/**
 * print_rev - Prints string in reverse
 * @argList: List of arguments
 * @outputBuffer: Buffer array to handle formatted output
 * @activeFlags: Calculates active flags
 * @width: get width
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Numbers of chars printed
 */

int print_rev(va_list argList, char outputBuffer[],
	int activeFlags, int width, int precision, int size)
{
	char *str;
	int i, count = 0;

	UNUSED(outputBuffer);
	UNUSED(activeFlags);
	UNUSED(width);
	UNUSED(size);

	str = va_arg(argList, char *);

	if (str == NULL)
	{
		UNUSED(precision);

		str = ")Null(";
	}
	for (i = 0; str[i]; i++)
		;

	for (i = i - 1; i >= 0; i--)
	{
		char z = str[i];

		write(1, &z, 1);
		count++;
	}
	return (count);
}

/************************* PRINT A STRING IN ROT13 *************************/
/**
 * print_rot13str - function that Print a string in rot13.
 * @argList: List of arguments
 * @outputBuffer: Buffer array to handle formatted output
 * @activeFlags: Calculates active flags
 * @width: get width
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Numbers of chars printed
 */
int print_rot13str(va_list argList, char outputBuffer[],
	int activeFlags, int width, int precision, int size)
{
	char x;
	char *str;
	unsigned int i, j;
	int count = 0;
	char in[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
	char out[] = "NOPQRSTUVWXYZABCDEFGHIJKLMnopqrstuvwxyzabcdefghijklm";

	str = va_arg(argList, char *);
	UNUSED(outputBuffer);
	UNUSED(activeFlags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);

	if (str == NULL)
		str = "(AHYY)";
	for (i = 0; str[i]; i++)
	{
		for (j = 0; in[j]; j++)
		{
			if (in[j] == str[i])
			{
				x = out[j];
				write(1, &x, 1);
				count++;
				break;
			}
		}
		if (!in[j])
		{
			x = str[i];
			write(1, &x, 1);
			count++;
		}
	}
	return (count);
}
