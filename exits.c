#include "custom_shell.h"

/**
 * custom_strncpy - copies a string up to a specified number of characters
 * @destination: the destination string to be copied to
 * @source: the source string
 * @limit: the maximum number of characters to copy
 * Return: the updated destination string
 */
char *custom_strncpy(char *destination, const char *source, size_t limit)
{
	size_t i;
	char *result = destination;

	for (i = 0; source[i] != '\0' && i < limit - 1; i++)
	{
		destination[i] = source[i];
	}
	while (i < limit)
	{
		destination[i] = '\0';
		i++;
	}

	return (result);
}

/**
 * custom_strncat - concatenates two strings up to a specified
 * number of characters
 * @destination: the first string
 * @source: the second string
 * @limit: the maximum number of characters to concatenate
 * Return: the concatenated string
 */
char *custom_strncat(char *destination, const char *source, size_t limit)
{
	size_t i, j;
	char *result = destination;

	for (i = 0; destination[i] != '\0'; i++)
		;

	for (j = 0; source[j] != '\0' && j < limit; j++)
	{
		destination[i] = source[j];
		i++;
	}

	if (j < limit)
		destination[i] = '\0';

	return (result);
}

/**
 * custom_strchr - locates a character in a string
 * @string: the string to be parsed
 * @character: the character to look for
 * Return: a pointer to the first occurrence of the character in the string,
 *         or NULL if the character is not found
 */
char *custom_strchr(char *string, char character)
{
	{do
	{
		if (*string == character)
			return (string);
	} while (*string++ != '\0');

	return (NULL);
}

