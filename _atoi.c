#include "custom_shell.h"
#include <unistd.h>
/**
 * check_interactive_mode - Checks if the shell is in interactive mode
 * @shell_info: Information struct for the shell
 *
 * Return: 1 if in interactive mode, 0 otherwise
 */
int check_interactive_mode(info_t *shell_info)
{
	return (isatty(STDIN_FILENO) && shell_info->read_file_descriptor <= 2);
}

/**
 * is_separator - Checks if a character is a separator
 * @character: The character to check
 * @separators: String containing separators
 *
 * Return: 1 if true, 0 if false
 */
int is_separator(char character, char *separators)
{
	while (*separators)
	{
		if (*separators++ == character)
			return (1);
	}
	return (0);
}

/**
 * is_alphabetic - Checks if a character is alphabetic
 * @c: The character to check
 *
 * Return: 1 if c is alphabetic, 0 otherwise
 */
int is_alphabetic(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	else
		return (0);
}

/**
 * convert_to_integer - Converts a string to an integer
 * @str: The string to be converted
 *
 * Return: 0 if no numbers in string, converted number otherwise
 */
int convert_to_integer(char *str)
{
	int index, sign = 1, flag = 0, result = 0;

	for (index = 0; str[index] != '\0' && flag != 2; index++)
	{
		if (str[index] == '-')
			sign *= -1;

		if (str[index] >= '0' && str[index] <= '9')
		{
			flag = 1;
			result *= 10;
			result += (str[index] - '0');
		}
		else if (flag == 1)
			flag = 2;
	}

if (sign == -1)
return (-result);
	else
return (result);
}

