#include "custom_shell.h"
#include <unistd.h>
/**
* safe_string_to_int - converts a string to an integer
* @str: the string to be converted
*
* Return: 0 if no numbers in string, converted number otherwise
*       -1 on error
*/
int safe_string_to_int(char *str)
{
int i = 0;
unsigned long int result = 0;

if (*str == '+')
str++;  /* TODO: why does this make main return 255? */
for (i = 0; str[i] != '\0'; i++)
{
if (str[i] >= '0' && str[i] <= '9')
{
result *= 10;
result += (str[i] - '0');
if (result > INT_MAX)
return (-1);
}
else
return (-1);
}
return (result);
}

/**
* print_custom_error - prints a custom error message
* @info: the parameter & return info struct
* @error_type: string containing specified error type
*
* Return: void
*/
void print_custom_error(info_t *info, char *error_type)
{
_eputs(info->fname);
_eputs(": ");
print_decimal(info->line_count, STDERR_FILENO);
_eputs(": ");
_eputs(info->argv[0]);
_eputs(": ");
_eputs(error_type);
}

/**
* print_decimal - function prints a decimal (integer) number (base 10)
* @input: the input
* @fd: the file descriptor to write to
*
* Return: number of characters printed
*/
int print_decimal(int input, int fd)
{
int (*__putchar)(char) = _putchar;
int i, count = 0;
unsigned int absolute_value, current;

if (fd == STDERR_FILENO)
__putchar = _eputchar;
if (input < 0)
{
absolute_value = -input;
__putchar('-');
count++;
}
else
absolute_value = input;
current = absolute_value;

for (i = 1000000000; i > 1; i /= 10)
{
if (absolute_value / i)
{
__putchar('0' + current / i);
count++;
}
current %= i;
}
__putchar('0' + current);
count++;

return (count);
}

/**
* convert_to_string - converter function, a clone of itoa
* @num: number
* @base: base
* @flags: argument flags
*
* Return: string
*/
char *convert_to_string(long int num, int base, int flags)
{
static char *array;
static char buffer[50];
char sign = 0;
char *ptr;
unsigned long n = num;

if (!(flags & CONVERT_UNSIGNED) && num < 0)
{
n = -num;
sign = '-';

}
array = flags & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
ptr = &buffer[49];
*ptr = '\0';

do {
*--ptr = array[n % base];
n /= base;
} while (n != 0);

if (sign)
*--ptr = sign;
return (ptr);
}

/**
* eliminate_comments - function replaces first instance of '#' with '\0'
* @buffer: address of the string to modify
*
* Return: void
*/
void eliminate_comments(char *buffer)
{
int i;

for (i = 0; buffer[i] != '\0'; i++)
if (buffer[i] == '#' && (!i || buffer[i - 1] == ' '))
{
buffer[i] = '\0';
break;
}
}

