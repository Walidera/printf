#include "holberton.h"

/************************* WRITE HANDLE *************************/
/**
 * handle_write_char - Prints a string
 * @c: char types.
 * @buffer: Buffer array to handle print
 * @flags:  Calculates active flags
 * @width: get width.
 * Return: Number of chars printed
 */
int handle_write_char(char c, char buffer[], int flags, int width)
{ /* char is stored at left and paddind at buffer's right */
	int i = 0;
	char padd = ' ';

	if (flags & F_ZERO)
		padd = '0';

	buffer[i++] = c;
	buffer[i] = '\0';

	if (width > 1)
	{
		buffer[BUFF_SIZE - 1] = '\0';
		for (i = 0; i < width - 1; i++)
			buffer[BUFF_SIZE - i - 2] = padd;

		if (flags & F_MINUS)
			return (write(1, &buffer[0], 1) +
					write(1, &buffer[BUFF_SIZE - i - 1], width - 1));
		else
			return (write(1, &buffer[BUFF_SIZE - i - 1], width - 1) +
					write(1, &buffer[0], 1));
	}

	return (write(1, &buffer[0], 1));
}

/************************* WRITE NUMBER *************************/
/**
 * write_number - Prints a string
 * @is_negative: Lista of arguments
 * @ind: char types.
 * @buffer: Buffer array to handle print
 * @flags:  Calculates active flags
 * @width: get width.
 * Return: Number of chars printed
 */
int write_number(int is_negative, int ind, char buffer[], int flags, int width)
{
	/* The number is stored at the bufer's right and starts at position i */
	int length = BUFF_SIZE - ind - 1, i = 0;
	char padd = ' ';
	char extra_ch = 0;

	if ((flags & F_ZERO) && !(flags & F_MINUS))
		padd = '0';

	if (is_negative)
		extra_ch = '-', length++;
	else if (flags & F_PLUS)
		extra_ch = '+', length++;
	else if (flags & F_SPACE)
		extra_ch = ' ', length++;

	if (width > length)
	{
		for (i = 1; i < width - length + 1; i++)
			buffer[i] = padd;

		buffer[i] = '\0';

		/* Asign extra char to left of buffer [buffer>padd]*/
		if (flags & F_MINUS && padd == ' ')
		{
			if (extra_ch)
				buffer[--ind] = extra_ch;
			return (write(1, &buffer[ind], length) +
					write(1, &buffer[1], i - 1));
		}
		/* Asign extra char to left of buffer [padd>buffer]*/
		else if (!(flags & F_MINUS) && padd == ' ')
		{
			if (extra_ch)
				buffer[--ind] = extra_ch;
			return (write(1, &buffer[1], i - 1) +
					write(1, &buffer[ind], length));
		}
		/* Asign extra char to left of padding [padd>buffer]*/
		else if (!(flags & F_MINUS) && padd == '0')
		{
			if (extra_ch)
				buffer[0] = extra_ch;
			return (write(1, &buffer[0], i) +
					write(1, &buffer[ind], length - 1));
		}
	}
	if (extra_ch)
		buffer[--ind] = extra_ch;

	return (write(1, &buffer[ind], length));
}

int write_unsigned(int is_negative, int ind,
char buffer[], int flags, int width)
{
	/* The number is stored at the bufer's right and starts at position i */
	int length = BUFF_SIZE - ind - 1, i = 0;
	char padd = ' ';

	UNUSED(is_negative);

	if ((flags & F_ZERO) && !(flags & F_MINUS))
		padd = '0';

	if (width > length)
	{
		for (i = 0; i < width - length; i++)
			buffer[i] = padd;

		buffer[i] = '\0';

		if (flags & F_MINUS) /* Asign extra char to left of buffer [buffer>padd]*/
		{
			return (write(1, &buffer[ind], length) +
					write(1, &buffer[0], i));
		}
		else /* Asign extra char to left of padding [padd>buffer]*/
		{
			return (write(1, &buffer[0], i) +
					write(1, &buffer[ind], length));
		}
	}

	return (write(1, &buffer[ind], length));
}
