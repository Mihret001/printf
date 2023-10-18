#include "main.h"

/*********************** HANDLE WRITE *************************/
/**
 * handle_write_chr - Prints a string
 * @ch: character type
 * @outputBuffer: Buffer array to handle formatted output
 * @activeFlags: calculates active flags.
 * @width: get width.
 * @precision: precision specifier
 * @size: Size specifier
 * Return: Number of chars printed.
 */

int handle_write_chr(char ch, char outputBuffer[],
	int activeFlags, int width, int precision, int size)
{ /* char is stored at left and paddind at buffer's right */
	int l = 0;
	char padd = ' ';

	UNUSED(precision);
	UNUSED(size);

	if (activeFlags & F_ZERO)
		padd = '0';

	outputBuffer[l++] = ch;
	outputBuffer[l] = '\0';

	if (width > 1)
	{
		outputBuffer[BUFF_SIZE - 1] = '\0';
		for (l = 0; l < width - 1; l++)
			outputBuffer[BUFF_SIZE - l - 2] = padd;

		if (activeFlags & F_MINUS)
			return (write(1, &outputBuffer[0], 1) +
					write(1, &outputBuffer[BUFF_SIZE - l - 1], width - 1));
		else
			return (write(1, &outputBuffer[BUFF_SIZE - l - 1], width - 1) +
					write(1, &outputBuffer[0], 1));
	}

	return (write(1, &outputBuffer[0], 1));
}

/************************* WRITE NUMBER *************************/
/**
 * write_number - prints a number
 * @is_negative: List of arguments
 * @ind: char types.
 * @outputBuffer: Buffer array to handle formatted output
 * @activeFlags: calculates active flags
 * @width: get width.
 * @precision: precision specifier
 * @size: Size specifier
 * Return: Number of chars printed.
 */

int write_number(int is_negative, int ind, char outputBuffer[],
	int activeFlags, int width, int precision, int size)
{
	int length = BUFF_SIZE - ind - 1;
	char padd = ' ', extra_ch = 0;

	UNUSED(size);

	if ((activeFlags & F_ZERO) && !(activeFlags & F_MINUS))
		padd = '0';
	if (is_negative)
		extra_ch = '-';
	else if (activeFlags & F_PLUS)
		extra_ch = '+';
	else if (activeFlags & F_SPACE)
		extra_ch = ' ';

	return (write_num(ind, outputBuffer, activeFlags, width, precision,
		length, padd, extra_ch));
}
/**
 * write_num - Write a number with a bufffer
 * @ind: Index at which the number starts on the buffer
 * @opBuffer: Buffer
 * @activeFlags: Flags
 * @width: width
 * @prec: Precision specifier
 * @length: Number length
 * @padd: Pading char
 * @extra_ch: Extra char
 * Return: Number of printed chars.
 */
int write_num(int ind, char opBuffer[], int activeFlags, int width,
	int prec, int length, char padd, char extra_ch)
{
	int l, padd_start = 1;

	if (prec == 0 && ind == BUFF_SIZE - 2 && opBuffer[ind] == '0' && width == 0)
		return (0);
	if (prec == 0 && ind == BUFF_SIZE - 2 && opBuffer[ind] == '0')
		opBuffer[ind] = padd = ' ';
	if (prec > 0 && prec < length)
		padd = ' ';
	while (prec > length)
		opBuffer[--ind] = '0', length++;
	if (extra_ch != 0)
		length++;
	if (width > length)
{
	for (l = 1; l < width - length + 1; l++)
		opBuffer[l] = padd;
	opBuffer[l] = '\0';
if (activeFlags & F_MINUS && padd == ' ')
{
if (extra_ch)
opBuffer[--ind] = extra_ch;
return (write(1, &opBuffer[ind], length) + write(1, &opBuffer[1], l - 1));
}
else if (!(activeFlags & F_MINUS) && padd == ' ')
{
if (extra_ch)
opBuffer[--ind] = extra_ch;
return (write(1, &opBuffer[1], l - 1) + write(1, &opBuffer[ind], length));
}
else if (!(activeFlags & F_MINUS) && padd == '0')
{
if (extra_ch)
opBuffer[--padd_start] = extra_ch;
return (write(1, &opBuffer[padd_start], l - padd_start) + write(1,
&opBuffer[ind], length - (1 - padd_start)));
}
	}
	if (extra_ch)
		opBuffer[--ind] = extra_ch;
	return (write(1, &opBuffer[ind], length));
}
/**
 * write_unsignd - Writes an unsigned num
 * @is_negative: Number indicating if the number is negative
 * @ind: Index in which the number starts in the buffer
 * @outputBuffer: Array of characters
 * @activeFlags: Flag specifiers
 * @width: Width specifier
 * @precision: Precision specifier
 * @size: Size specifier
 * Return: Number of written characters.
 */
int write_unsignd(int is_negative, int ind, char outputBuffer[],
	int activeFlags, int width, int precision, int size)
{
	int length = BUFF_SIZE - ind - 1, l = 0;
	char padd = ' ';

	UNUSED(is_negative);
	UNUSED(size);

	if (precision == 0 && ind == BUFF_SIZE - 2 && outputBuffer[ind] == '0')
		return (0); /* printf(".0d", 0)  no char is printed */
	if (precision > 0 && precision < length)
		padd = ' ';
	while (precision > length)
	{
		outputBuffer[--ind] = '0';
		length++;
	}
	if ((activeFlags & F_ZERO) && !(activeFlags & F_MINUS))
		padd = '0';
	if (width > length)
	{
		for (l = 0; l < width - length; l++)
			outputBuffer[l] = padd;

		outputBuffer[l] = '\0';

		if (activeFlags & F_MINUS)
		{
			return (write(1, &outputBuffer[ind], length) + write
					(1, &outputBuffer[0], l));
		}
		else
		{
			return (write(1, &outputBuffer[0], l) + write(1,
						&outputBuffer[ind], length));
		}
	}
	return (write(1, &outputBuffer[ind], length));
}
/**
 * write_pointer - Writes the address of a memory
 * @outputBuffer: Arrays of characters
 * @ind: Index at which the number starts in the buffer
 * @length: Length of number
 * @width: Wwidth specifier
 * @activeFlags: Flags specifier
 * @padd: Char representing the padding
 * @extra_ch: Char representing extra char
 * @padd_start: Index at which padding should start
 * Return: Number of written chars.
 */

int write_pointer(char outputBuffer[], int ind, int length,
	int width, int activeFlags, char padd, char extra_ch, int padd_start)
{
	int l;

	if (width > length)
	{
		for (l = 3; l < width - length + 3; l++)
			outputBuffer[l] = padd;
		outputBuffer[l] = '\0';
		if (activeFlags & F_MINUS && padd == ' ')
		{
			outputBuffer[--ind] = 'x';
			outputBuffer[--ind] = '0';
			if (extra_ch)
				outputBuffer[--ind] = extra_ch;
			return (write(1, &outputBuffer[ind], length) + write(1, &outputBuffer[3],
						l - 3));
		}
		else if (!(activeFlags & F_MINUS) && padd == ' ')
		{
			outputBuffer[--ind] = 'x';
			outputBuffer[--ind] = '0';
			if (extra_ch)
				outputBuffer[--ind] = extra_ch;
			return (write(1, &outputBuffer[3], l - 3) + write(1, &outputBuffer[ind],
						length));
		}
		else if (!(activeFlags & F_MINUS) && padd == '0')
		{
			if (extra_ch)
				outputBuffer[--padd_start] = extra_ch;
			outputBuffer[1] = '0';
			outputBuffer[2] = 'x';
			return (write(1, &outputBuffer[padd_start], l - padd_start) +
				write(1, &outputBuffer[ind], length - (1 - padd_start) - 2));
		}
	}
	outputBuffer[--ind] = 'x';
	outputBuffer[--ind] = '0';
	if (extra_ch)
		outputBuffer[--ind] = extra_ch;
	return (write(1, &outputBuffer[ind], BUFF_SIZE - ind - 1));
}
