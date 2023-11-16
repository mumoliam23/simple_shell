#include "custom_shell.h"

/**
* exit_shell - exits the shell
* @info: Structure containing potential arguments.
* Return: Exits with a given exit status (0) if info->argv[0] != "exit"
*/
int exit_shell(info_t *info)
{
int exit_code;

if (info->argv[1])  /* If there is an exit argument */
{
exit_code = _erratoi(info->argv[1]);
if (exit_code == -1)
{
info->status = 2;
print_error(info, "Illegal number: ");
_eputs(info->argv[1]);
_eputchar('\n');
return (1);
}
info->err_num = exit_code;
return (-2);
}

info->err_num = -1;
return (-2);
}

/**
* change_directory - changes the current directory of the process
* @info: Structure containing potential arguments.
* Return: Always 0
*/
int change_directory(info_t *info)
{
char *cwd, *dir, buffer[1024];
int chdir_result;

cwd = getcwd(buffer, 1024);
if (!cwd)
_puts("TODO: >>getcwd failure emsg here<<\n");

if (!info->argv[1])
{
dir = _getenv(info, "HOME=");
if (!dir)
chdir_result = chdir((dir = _getenv(info, "PWD=")) ? dir : "/");
else
chdir_result = chdir(dir);
}
else if (_strcmp(info->argv[1], "-") == 0)
{
if (!_getenv(info, "OLDPWD="))
{
_puts(cwd);
_putchar('\n');
return (1);
}
_puts(_getenv(info, "OLDPWD=")), _putchar('\n');
chdir_result = chdir((dir = _getenv(info, "OLDPWD=")) ? dir : "/");
}
else
chdir_result = chdir(info->argv[1]);
if (chdir_result == -1)
{
print_error(info, "can't cd to ");
_eputs(info->argv[1]), _eputchar('\n');
}
else
{
_setenv(info, "OLDPWD", _getenv(info, "PWD="));
_setenv(info, "PWD", getcwd(buffer, 1024));
}
return (0);
}
/**
* display_help - displays help information.
* @info: Structure containing potential arguments.
* Return: Always 0
*/
int display_help(info_t *info)
{
char **arg_array;
arg_array = info->argv;
_puts("help call works. Function not yet implemented \n");
if (0)
_puts(*arg_array); /* temp att_unused workaround */
return (0);
}

