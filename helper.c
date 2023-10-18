#include "main.h"

/**
 * is_printable - Evaluates if a character is printable or not
 * @ch: Character to be evaluated.
 * Return: 1 if c is printable, 0 otherwise
 */

int is_printable(char ch)
{
	if (ch >= 32 && ch < 127)
		return (1);

	return (0);
}

/**
 * append_hexaDeCode - appends an ascci in hexadec code to the outputbuffer
 * @outputBuffer: Array of chars.
 * @l: Index at which to start appending.
 * @ascii_code: ASSCI CODE.
 * Return: Always 3
 */

int append_hexaDeCode(char ascii_code, char outputBuffer[], int l)
{
	char mapTo[] = "0123456789ABCDEF";
	/* The hexa format code is always 2 digits long */
	if (ascii_code < 0)
		ascii_code *= -1;

	outputBuffer[l++] = '\\';
	outputBuffer[l++] = 'x';

	outputBuffer[l++] = mapTo[ascii_code / 16];
	outputBuffer[l] = mapTo[ascii_code % 16];

	return (3);
}

/**
 * is_digit - checks if a character is a digit or not
 * @ch: the character to be evaluated
 * Return: 1 if c is a digit, 0 otherwise
 */

int is_digit(char ch)
{
	if (ch >= '0' && ch <= '9')
		return (1);

	return (0);
}

/**
 * convert_size_number - directs a number to the specified size
 * @number: Number to be directed.
 * @size: Number indicating the type to be casted.
 * Return: directed value of number
 */

long int convert_size_number(long int number, int size)
{
	if (size == S_LONG)
		return (number);
	else if (size == S_SHORT)
		return ((short)number);

	return ((int)number);
}

/**
 * convert_size_unsignd - directs a number to the specified size
 * @number: Number to be directed
 * @size: Number indicating the type to be casted
 * Return: directed value of num
 */

long int convert_size_unsignd(unsigned long int number, int size)
{
	if (size == S_LONG)
		return (number);
	else if (size == S_SHORT)
		return ((unsigned short)number);

	return ((unsigned int)number);
}
