#include "custom_shell.h"
/**
* display_history - displays the command history with line numbers.
* @info: Structure containing potential arguments.
* Return: Always 0
*/
int display_history(info_t *info)
{
print_list(info->history);
return (0);
}
/**
* remove_alias - removes an alias from the list.
* @info: parameter struct.
* @str: the string alias.
* Return: Always 0 on success, 1 on error.
*/
int remove_alias(info_t *info, char *str)
{
char *equal_sign, saved_char;
int result;
equal_sign = _strchr(str, '=');
if (!equal_sign)
return (1);
saved_char = *equal_sign;
*equal_sign = '\0';
result = delete_node_at_index(&(info->alias),
get_node_index(info->alias, node_starts_with(info->alias, str, -1)));
*equal_sign = saved_char;
return (result);
}
/**
* add_alias - adds an alias to the list.
* @info: parameter struct.
* @str: the string alias.
* Return: Always 0 on success, 1 on error.
*/
int add_alias(info_t *info, char *str)
{
char *equal_sign;
equal_sign = _strchr(str, '=');
if (!equal_sign)
return (1);
if (!*++equal_sign)
return (remove_alias(info, str));
remove_alias(info, str);
return (add_node_end(&(info->alias), str, 0) == NULL);
}
/**
* print_alias_entry - prints an alias string.
* @node: the alias node.
* Return: Always 0 on success, 1 on error.
*/
int print_alias_entry(list_t *node)
{
char *equal_sign = NULL, *alias_part = NULL;
if (node)
{
equal_sign = _strchr(node->str, '=');
for (alias_part = node->str; alias_part <= equal_sign; alias_part++)
_putchar(*alias_part);
_putchar('\'');
_puts(equal_sign + 1);
_puts("'\n");
return (0);
}
return (1);
}
/**
* manage_alias - mimics the alias builtin (man alias).
* @info: Structure containing potential arguments.
* Return: Always 0
*/
int manage_alias(info_t *info)
{
int i = 0;
char *equal_sign = NULL;
list_t *node = NULL;
if (info->argc == 1)
{
node = info->alias;
while (node)
{
print_alias_entry(node);
node = node->next;
}
return (0);
}
for (i = 1; info->argv[i]; i++)
{
equal_sign = _strchr(info->argv[i], '=');
if (equal_sign)
add_alias(info, info->argv[i]);
else
print_alias_entry(node_starts_with(info->alias, info->argv[i], '='));
}
return (0);
}

