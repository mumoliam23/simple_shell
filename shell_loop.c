#include "custom_shell.h"

/**
* shell_loop - main shell loop
* @info: the parameter & return info struct
* @av: the argument vector from main()
*
* Return: 0 on success, 1 on error, or error code
*/
int shell_loop(info_t *info, char **av)
{
ssize_t input_length = 0;
int builtin_ret = 0;

while (input_length != -1 && builtin_ret != -2)
{
clear_info(info);
if (interactive(info))
_puts("$ ");
_eputchar(BUF_FLUSH);
input_length = get_input(info);
if (input_length != -1)
{
set_info(info, av);
builtin_ret = find_builtin_command(info);
if (builtin_ret == -1)
find_external_command(info);
}
else if (interactive(info))
_putchar('\n');
free_info(info, 0);
}
write_history(info);
free_info(info, 1);
if (!interactive(info) && info->status)
exit(info->status);
if (builtin_ret == -2)
{
if (info->err_num == -1)
exit(info->status);
exit(info->err_num);
}
return (builtin_ret);
}

/**
* find_builtin_command - finds a builtin command
* @info: the parameter & return info struct
*
* Return: -1 if builtin not found,
*			0 if builtin executed successfully,
*			1 if builtin found but not successful,
*			-2 if builtin signals exit()
*/
int find_builtin_command(info_t *info)
{
int i, builtin_ret = -1;
builtin_table builtintbl[] = {
{"exit", my_exit},
{"env", my_env},
{"help", my_help},
{"history", my_history},
{"setenv", my_setenv},
{"unsetenv", my_unsetenv},
{"cd", my_cd},
{"alias", my_alias},
{NULL, NULL}
};

for (i = 0; builtintbl[i].type; i++)
if (_strcmp(info->argv[0], builtintbl[i].type) == 0)
{
info->line_count++;
builtin_ret = builtintbl[i].func(info);
break;
}
return (builtin_ret);
}

/**
* find_external_command - finds a command in PATH
* @info: the parameter & return info struct
*
* Return: void
*/
void find_external_command(info_t *info)
{
char *path = NULL;

info->path = info->argv[0];
if (info->linecount_flag == 1)
{
info->line_count++;
info->linecount_flag = 0;
}
int argument_count = count_nonempty_arguments(info->arg);
if (!argument_count)
return;

path = find_path(info, _getenv(info, "PATH="), info->argv[0]);
if (path)
{
info->path = path;
fork_external_command(info);
}
else
{
if ((interactive(info) || _getenv(info, "PATH=")
|| info->argv[0][0] == '/') && is_command(info, info->argv[0]))
fork_external_command(info);
else if (*(info->arg) != '\n')
{
info->status = 127;
print_error(info, "not found\n");
}
}
}

/**
* fork_external_command - forks an exec thread to run cmd
* @info: the parameter & return info struct
*
* Return: void
*/
void fork_external_command(info_t *info)
{
pid_t child_pid;

child_pid = fork();
if (child_pid == -1)
{
perror("Error:");
return;
}
if (child_pid == 0)
{
if (execve(info->path, info->argv, get_environ(info)) == -1)
{
free_info(info, 1);
if (errno == EACCES)
exit(126);
exit(1);
}
}
else
{
wait(&(info->status));
if (WIFEXITED(info->status))
{
info->status = WEXITSTATUS(info->status);
if (info->status == 126)
print_error(info, "Permission denied\n");
}
}
}


