#include "shell.h"

/**
* retrieve_environment - returns a copy of the environment as a string array
* @info: Structure containing potential arguments.
* Return: Always 0
*/
char **retrieve_environment(info_t *info)
{
if (!info->environment || info->env_updated)
{
info->environment = list_to_strings(info->env);
info->env_updated = 0;
}

return (info->environment);
}

/**
* remove_environment_variable - Remove an environment variable
* @info: Structure containing potential arguments.
* @variable: the environment variable to be removed
* Return: 1 on successful removal, 0 otherwise
*/
int remove_environment_variable(info_t *info, char *variable)
{
list_t *node = info->env;
size_t index = 0;
char *prefix;

if (!node || !variable)
return (0);

while (node)
{
prefix = starts_with(node->str, variable);
if (prefix && *prefix == '=')
{
info->env_updated = delete_node_at_index(&(info->env), index);
index = 0;
node = info->env;
continue;
}
node = node->next;
index++;
}
return (info->env_updated);
}

/**
* set_environment_variable - Initialize a new environment variable
*                            or modify an existing one
* @info: Structure containing potential arguments.
* @variable: the environment variable to be set or modified
* @value: the value of the environment variable
* Return: Always 0
*/
int set_environment_variable(info_t *info, char *variable, char *value)
{
char *buffer = NULL;
list_t *node;
char *prefix;

if (!variable || !value)
return (0);

buffer = malloc(_strlen(variable) + _strlen(value) + 2);
if (!buffer)
return (1);
_strcpy(buffer, variable);
_strcat(buffer, "=");
_strcat(buffer, value);
node = info->env;
while (node)
{
prefix = starts_with(node->str, variable);
if (prefix && *prefix == '=')
{
free(node->str);
node->str = buffer;
info->env_updated = 1;
return (0);
}
node = node->next;
}
add_node_end(&(info->env), buffer, 0);
free(buffer);
info->env_updated = 1;
return (0);
}

