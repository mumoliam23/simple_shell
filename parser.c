#include "custom_shell.h"

/**
* is_executable - determines if a file is an executable command
* @path: path to the file
*
* Return: 1 if true, 0 otherwise
*/
int is_executable(char *path)
{
struct stat st;

if (!path || stat(path, &st))
return (0);

return ((st.st_mode & S_IFREG) != 0);
}

/**
* extract_path_segment - extracts a segment from the PATH string
* @pathstr: the PATH string
* @start: starting index
* @stop: stopping index
*
* Return: pointer to the extracted path segment
*/
char *extract_path_segment(char *pathstr, int start, int stop)
{
static char buf[1024];
int i, k = 0;

for (i = start; i < stop; i++)
if (pathstr[i] != ':')
buf[k++] = pathstr[i];
buf[k] = '\0';
return (buf);
}

/**
* find_executable_in_path - finds the executable in the PATH string
* @info: the info struct
* @pathstr: the PATH string
* @cmd: the command to find
*
* Return: full path of the command if found, or NULL
*/
char *find_executable_in_path(info_t *info, char *pathstr, char *cmd)
{
int i = 0, curr_pos = 0;
char *path;

if (!pathstr)
return (NULL);

if (_strlen(cmd) > 2 && starts_with(cmd, "./") && is_executable(cmd))
return (cmd);

while (1)
{
if (!pathstr[i] || pathstr[i] == ':')
{
path = extract_path_segment(pathstr, curr_pos, i);

if (!_strlen(path))
_strcat(path, cmd);
else
{
_strcat(path, "/");
_strcat(path, cmd);
}

if (is_executable(path))
return (path);

if (!pathstr[i])
break;

curr_pos = i;
}
i++;
}
return (NULL);
}

