#include "main.h"

/************************ PRINT UNSIGNED NUMBER *************************/
/**
 * printFormattedUnsigned - Prints an unsigned number in the desired format
 * @argList: List a of arguments.
 * @outputBuffer: Buffer array to handle formatted output.
 * @activeFlags:  Calculates the available active flags
 * @width: gets width
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Number of chars printed.
 */
int printFormattedUnsigned(va_list argList, char outputBuffer[],
	int activeFlags, int width, int precision, int size)
{
	int i = BUFF_SIZE - 2;
	unsigned long int number = va_arg(argList, unsigned long int);

	number = convert_size_unsignd(number, size);

	if (number == 0)
		outputBuffer[i--] = '0';

	outputBuffer[BUFF_SIZE - 1] = '\0';

	while (number > 0)
	{
		outputBuffer[i--] = (number % 10) + '0';
		number /= 10;
	}

	i++;

	return (write_unsignd(0, i, outputBuffer, activeFlags,
				width, precision, size));
}

/*************** PRINT UNSIGNED NUMBER IN OCTAL NOTATION ***************/
/**
 * printFormattedUnsigned - Prints an unsigned number in the octal notation.
 * @argList: List a of arguments.
 * @outputBuffer: Buffer array to handle formatted output.
 * @activeFlags: Calculates the available active flags
 * @width: gets width
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Number of chars printed.
 */

int printFormattedOctal(va_list argList, char outputBuffer[],
	int activeFlags, int width, int precision, int size)
{
	int i = BUFF_SIZE - 2;
	unsigned long int number = va_arg(argList, unsigned long int);
	unsigned long int init_num = number;

	UNUSED(width);

	number = convert_size_unsignd(number, size);

	if (number == 0)
		outputBuffer[i--] = '0';

	outputBuffer[BUFF_SIZE - 1] = '\0';

	while (number > 0)
	{
		outputBuffer[i--] = (number % 8) + '0';
		number /= 8;
	}

	if (activeFlags & F_HASH && init_num != 0)
		outputBuffer[i--] = '0';

	i++;

	return (write_unsignd(0, i, outputBuffer, activeFlags,
				width, precision, size));
}

/**************** PRINT UNSIGNED NUMBER IN HEXADECIMAL  ********************/
/**
 * printFormattedHexadecimal - Prints unsgnd number in the HEXADECIMAL format
 * @argList: List a of arguments.
 * @outputBuffer: Buffer array to handle formatted output.
 * @activeFlags: Calculates the available active flags
 * @width: gets width
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Number of chars printed.
 */

int printFormattedHexadecimal(va_list argList, char outputBuffer[],
	int activeFlags, int width, int precision, int size)
{
	return (print_hexadec(argList, "0123456789abcdef", outputBuffer,
		activeFlags, 'x', width, precision, size));
}

/******************** PRINT UNSIGNED NUM IN UPPER HEXADEC ******************/
/**
 * printFormattedUnsigned - Prints unsgnd number in upper hexadecimal format
 * @argList: List a of arguments.
 * @outputBuffer: Buffer array to handle formatted output.
 * @activeFlags: Calculates the available active flags
 * @width: gets width
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Number of chars printed.
 */

int printFormattedHexaUpper(va_list argList, char outputBuffer[],
	int activeFlags, int width, int precision, int size)
{
	return (print_hexadec(argList, "0123456789ABCDEF", outputBuffer,
		activeFlags, 'X', width, precision, size));
}

/************** PRINT HEXADECIMAL NUMBER IN LOWER OR UPPER **************/
/**
 * print_hexadec - Prints a hexadecimal number in lower or upper format.
 * @argList: List of arguments
 * @mapTo: Array of values to map the number to
 * @outputBuffer: Buffer array to handle formatted output.
 * @activeFlags: Calculates active flags
 * @flag_ch: Calculates active flags
 * @width: get width
 * @precision: Precision specification
 * @size: Size specifier
 * @size: Size specification
 * Return: Number of chars printed
 */

int print_hexadec(va_list argList, char mapTo[], char outputBuffer[],
	int activeFlags, char flag_ch, int width, int precision, int size)
{
	int i = BUFF_SIZE - 2;
	unsigned long int number = va_arg(argList, unsigned long int);
	unsigned long int init_num = number;

	UNUSED(width);

	number = convert_size_unsignd(number, size);

	if (number == 0)
		outputBuffer[i--] = '0';

	outputBuffer[BUFF_SIZE - 1] = '\0';

	while (number > 0)
	{
		outputBuffer[i--] = mapTo[number % 16];
		number /= 16;
	}

	if (activeFlags & F_HASH && init_num != 0)
	{
		outputBuffer[i--] = flag_ch;
		outputBuffer[i--] = '0';
	}

	i++;

	return (write_unsignd(0, i, outputBuffer, activeFlags,
				width, precision, size));
}
