#include "main.h"

/************************* PRINT FORMATTED CHARACTER *************************/
/**
 * printFormattedCharacter - Prints a character
 * @argList: List of arguments.
 * @outputBuffer: Buffer array to handle print.
 * @activeFlags: Flags indicating the formatting options.
 * @width: Width of the output field.
 * @precision: Precision specification.
 * @size: Size specifier.
 * Return: Number of characters printed.
 */

int printFormattedCharacter(va_list argList, char outputBuffer[],
		int activeFlags, int width, int precision, int size)
{
	char ch = va_arg(argList, int);

	return (handle_write_chr(ch, outputBuffer, activeFlags,
				width, precision, size));
}
/************************* PRINT FORMATTED STRING *************************/
/**
 * printFormattedString - Prints a string
 * @argList: List of arguments.
 * @outputBuffer: Buffer array to handle print.
 * @activeFlags: Flags indicating the formatting options.
 * @width: Width of the output field.
 * @precision: Precision specification.
 * @size: Size specifier.
 * Return: Number of characters printed.
 */

int printFormattedString(va_list argList, char outputBuffer[],
		int activeFlags, int width, int precision, int size)
{
	int len = 0, l;
	char *s = va_arg(argList, char *);

	UNUSED(outputBuffer);
	UNUSED(activeFlags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);

	if (s == NULL)
	{
		s = "(null)";
		if (precision >= 6)
			s = "      ";
	}

	while (s[len] != '\0')
		len++;
	if (precision >= 0 && precision < len)
		len = precision;
	if (width > len)
	{
		if (activeFlags & F_MINUS)
		{
			write(1, &s[0], len);
			for (l = width - len; l > 0; l--)
			write(1, " ", 1);
			return (width);
		}
		else
		{
			for (l = width - len; l > 0; l--)
				write(1, " ", 1);
			write(1, &s[0], len);
			return (width);
		}
	}
	return (write(1, s, len));
}

/************************* PRINT FORMATTED PERCENT SIGN ******************/
/**
 * printFormattedPercentSign - Prints a percent sign
 * @argList: List of arguments.
 * @outputBuffer: Buffer array to handle print.
 * @activeFlags: Flags indicating the formatting options.
 * @width: Width of the output field.
 * @precision: Precision specification.
 * @size: Size specifier.
 * Return: Number of characters printed.
 */

int printFormattedPercentSign(va_list argList, char outputBuffer[],
		int activeFlags, int width, int precision, int size)
{
	UNUSED(argList);
	UNUSED(outputBuffer);
	UNUSED(activeFlags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);

	return (write(1, "%%", 1));
}

/********************* PRINT FORMATTED INTEGER *********************/
/**
 * printFormattedInteger - Prints an integer
 * @argList: List of arguments.
 * @outputBuffer: Buffer array to handle print.
 * @activeFlags: Flags indicating the formatting options.
 * @width: Width of the output field.
 * @precision: Precision specification.
 * @size: Size specifier.
 * Return: Number of characters printed.
 */

int printFormattedInteger(va_list argList, char outputBuffer[],
		int activeFlags, int width, int precision, int size)
{
	int x = BUFF_SIZE - 2;
		int neg = 0;
		long int no = va_arg(argList, long int);
		unsigned long int number;

		no = convert_size_number(no, size);

		if (no == 0)
			outputBuffer[x--] = '0';

		outputBuffer[BUFF_SIZE - 1] = '\0';
		number = (unsigned long int)no;

		if (no < 0)
		{
			number = (unsigned long int)((-1) * no);
			neg = 1;
		}

		while (number > 0)
		{
			outputBuffer[x--] = (number % 10) + '0';
			number /= 10;
		}

		x++;

		return (write_number(neg, x, outputBuffer, activeFlags,
				width, precision, size));
}

/************************* PRINT FORMATTED BINARY *************************/
/**
 * printFormattedBinary - Prints an unsigned number in binary format
 * @argList: List of arguments.
 * @outputBuffer: Buffer array to handle print.
 * @activeFlags: Flags indicatingthe formatting options.
 * @width: Width of the output field.
 * @precision: Precision specification.
 * @size: Size specifier.
 * Return: Number of characters printed.
 */
int printFormattedBinary(va_list argList, char outputBuffer[],
		int activeFlags, int width, int precision, int size)
{
	unsigned int a, b, c, ans;
	unsigned int d[32];
	int num;

	UNUSED(outputBuffer);
	UNUSED(activeFlags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);

	a = va_arg(argList, unsigned int);
	b = 2147483648;
	d[0] = a / b;

	for (c = 1; c < 32; c++)
	{
		b /= 2;
		d[c] = (a / b) % 2;
	}
	for (c = 0, ans = 0, num = 0; c < 32; c++)
	{
		ans += d[c];
		if (ans || c == 31)
		{
			char z = '0' + d[c];

			write(1, &z, 1);
			num++;
		}
	}
	return (num);
}
