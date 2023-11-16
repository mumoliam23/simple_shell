#include "custom_shell.h"

/**
* initialize_info - initializes fields in the info_t struct
* @info: struct address
*/
void initialize_info(info_t *info)
{
info->arg = NULL;
info->argv = NULL;
info->path = NULL;
info->argc = 0;
}

/**
* populate_info - populates info_t struct with command line arguments
* @info: struct address
* @argument_vector: argument vector
*/
void populate_info(info_t *info, char **argument_vector)
{
int i = 0;

info->fname = argument_vector[0];
if (info->arg)
{
info->argv = strtow(info->arg, " \t");
if (!info->argv)
{
info->argv = malloc(sizeof(char *) * 2);
if (info->argv)
{
info->argv[0] = _strdup(info->arg);
info->argv[1] = NULL;
}
}
for (i = 0; info->argv && info->argv[i]; i++)
;
info->argc = i;

replace_alias(info);
replace_vars(info);
}
}

/**
* release_info_resources - frees allocated memory in the info_t struct
* @info: struct address
* @free_all: true if freeing all fields
*/
void release_info_resources(info_t *info, int free_all)
{
ffree(info->argv);
info->argv = NULL;
info->path = NULL;
if (free_all)
{
if (!info->cmd_buf)
free(info->arg);
if (info->env)
free_list(&(info->env));
if (info->history)
free_list(&(info->history));
if (info->alias)
free_list(&(info->alias));
ffree(info->environ);
info->environ = NULL;
bfree((void **)info->cmd_buf);
if (info->readfd > 2)
close(info->readfd);
_putchar(BUF_FLUSH);
}
}

