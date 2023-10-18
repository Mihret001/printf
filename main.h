#ifndef MAIN_H
#define MAIN_H
#include <stdarg.h>
#include <stdio.h>
#include <unistd.h>

#define UNUSED(x) (void)(x)
#define BUFF_SIZE 1024

/* FLAGS */
#define F_MINUS 1
#define F_PLUS 2
#define F_ZERO 4
#define F_HASH 8
#define F_SPACE 16

/* SIZES */
#define S_LONG 2
#define S_SHORT 1

/**
 * struct formatStr - Struct op
 *
 * @formatStr: The format.
 * @fn: The function associated.
 */
struct formatStr
{
	char formatStr;
	int (*fn)(va_list, char[], int, int, int, int);
};


/**
 * typedef struct formatStr formatStr_t - Struct op
 *
 * @formatStr: The format.
 * @fm_t: The function associated.
 */
typedef struct formatStr formatStr_t;

int _printf(const char *formatStr, ...);
int handle_print(const char *formatStr, int *i,
va_list arg_list, char outputBuffer[], int activeFlags,
int width, int precision, int size);

/****************** FUNCTIONS ******************/

/* Funtions to print chars and strings */

int printFormattedCharacter(va_list argList, char outputBuffer[],
		int activeFlags, int width, int precision, int size);
int printFormattedString(va_list argList, char outputBuffer[],
		int activeFlags, int width, int precision, int size);
int printFormattedPercentSign(va_list argList, char outputBuffer[],
		int activeFlags, int width, int precision, int size);

/* Functions to print numbers */

int printFormattedInteger(va_list argList, char outputBuffer[],
		int activeFlags, int width, int precision, int size);
int printFormattedBinary(va_list argList, char outputBuffer[],
		int activeFlags, int width, int precision, int size);
int printFormattedUnsigned(va_list argList, char outputBuffer[],
	int activeFlags, int width, int precision, int size);
int printFormattedOctal(va_list argList, char outputBuffer[],
	int activeFlags, int width, int precision, int size);
int printFormattedHexadecimal(va_list argList, char outputBuffer[],
	int activeFlags, int width, int precision, int size);
int printFormattedHexaUpper(va_list argList, char outputBuffer[],
	int activeFlags, int width, int precision, int size);
int print_hexadec(va_list argList, char mapTo[], char outputBuffer[],
	int activeFlags, char flag_ch, int width, int precision, int size);

/* Function to print non printable characters */
int print_NonPrintable(va_list argList, char outputBuffer[],
	int activeFlags, int width, int precision, int size);

/* Function to print memory address */
int printFormattedPointer(va_list argList, char outputBuffer[],
	int activeFlags, int width, int precision, int size);

/* Functions to handle other specifiers */
int handle_flags(const char *formatStr, int *l);
int handle_width(const char *formatStr, int *l, va_list arg_list);
int handle_precision(const char *formatStr, int *l, va_list arg_list);
int handle_size(const char *formatStr, int *l);

/*Function to print string in reverse*/
int print_rev(va_list argList, char outputBuffer[],
	int activeFlags, int width, int precision, int size);

/*Function to print a string in rot 13*/
int print_rot13str(va_list argList, char outputBuffer[],
	int activeFlags, int width, int precision, int size);

/* width handler */
int handle_write_chr(char ch, char outputBuffer[],
	int activeFlags, int width, int precision, int size);
int write_number(int is_negative, int ind, char outputBuffer[],
	int activeFlags, int width, int precision, int size);
int write_num(int ind, char opBuffer[], int activeFlags, int width,
	int prec, int length, char padd, char extra_ch);
int write_unsignd(int is_negative, int ind, char outputBuffer[],
	int activeFlags, int width, int precision, int size);
int write_pointer(char outputBuffer[], int ind, int length,
	int width, int activeFlags, char padd, char extra_ch, int padd_start);

/***************  HELPERS  ******************/
int is_printable(char ch);
int append_hexaDeCode(char ascii_code, char outputBuffer[], int l);
int is_digit(char ch);

long int convert_size_number(long int number, int size);
long int convert_size_unsignd(unsigned long int number, int size);

#endif
