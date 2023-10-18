#include "main.h"

/**
 * handle_flags - a function calculating active flags
 * @formatStr: a formatted string which is used to print the arguments
 * @l: takes a parameter.
 * Return: Flags
 */

int handle_flags(const char *formatStr, int *l)
{
	/* - + 0 # ' ' */
	/* 1 2 4 8  16 */
	int m, curr_l;
	int activeFlags = 0;
	const char FLAGS_CH[] = {'-', '+', '0', '#', ' ', '\0'};
	const int FLAGS_ARR[] = {F_MINUS, F_PLUS, F_ZERO, F_HASH, F_SPACE, 0};

	for (curr_l = *l + 1; formatStr[curr_l] != '\0'; curr_l++)
	{
		for (m = 0; FLAGS_CH[m] != '\0'; m++)
			if (formatStr[curr_l] == FLAGS_CH[m])
			{
				activeFlags |= FLAGS_ARR[m];
				break;
			}

		if (FLAGS_CH[m] == 0)
			break;
	}

	*l = curr_l - 1;

	return (activeFlags);
}
