#include "custom_shell.h"

/**
* list_length - determines the length of a linked list
* @head: pointer to the first node
*
* Return: size of the list
*/
size_t list_length(const list_t *head)
{
size_t count = 0;

while (head)
{
head = head->next;
count++;
}
return (count);
}

/**
* list_to_strings - returns an array of strings from the list->str
* @head: pointer to the first node
*
* Return: array of strings
*/
char **list_to_strings(list_t *head)
{
list_t *node = head;
size_t len = list_length(head);
char **strings;
char *str;

if (!head || !len)
return (NULL);

strings = malloc(sizeof(char *) * (len + 1));
if (!strings)
return (NULL);

for (size_t i = 0; node; node = node->next, i++)
{
str = _strdup(node->str);
if (!str)
{
for (size_t j = 0; j < i; j++)
free(strings[j]);
free(strings);
return (NULL);
}
strings[i] = str;
}
strings[len] = NULL;
return (strings);
}

/**
* print_list - prints all elements of a list_t linked list
* @head: pointer to the first node
*
* Return: size of the list
*/
size_t print_list(const list_t *head)
{
size_t count = 0;

while (head)
{
_puts(convert_number(head->num, 10, 0));
_putchar(':');
_putchar(' ');
_puts(head->str ? head->str : "(nil)");
_puts("\n");
head = head->next;
count++;
}
return (count);
}

/**
* find_node_with_prefix - returns a node whose string starts with a prefix
* @head: pointer to the list head
* @prefix: string to match
* @c: the next character after the prefix to match (-1 to ignore)
*
* Return: matching node or NULL
*/
list_t *find_node_with_prefix(list_t *head, char *prefix, char c)
{
char *p = NULL;

while (head)
{
p = starts_with(head->str, prefix);
if (p && ((c == -1) || (*p == c)))
return (head);
head = head->next;
}
return (NULL);
}

/**
* get_node_index - gets the index of a node
* @head: pointer to the list head
* @node: pointer to the node
*
* Return: index of the node or -1
*/
ssize_t get_node_index(list_t *head, list_t *node)
{
size_t index = 0;

while (head)
{
if (head == node)
return (index);
head = head->next;
index++;
}
return (-1);
}

