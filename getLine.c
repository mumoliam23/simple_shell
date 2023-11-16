#include "shell.h"

/**
* buffer_input - buffers chained commands
* @info: parameter struct
* @buffer: address of buffer
* @buffer_size: address of buffer size variable
*
* Return: bytes read
*/
ssize_t buffer_input(info_t *info, char **buffer, size_t *buffer_size)
{
ssize_t read_size = 0;
size_t buffer_position = 0;

if (!*buffer_size) /* if nothing left in the buffer, fill it */
{
free(*buffer);
*buffer = NULL;
signal(SIGINT, sigintHandler);
#if USE_GETLINE
read_size = getline(buffer, buffer_size, stdin);
#else
read_size = custom_getline(info, buffer, buffer_size);
#endif
if (read_size > 0)
{
if ((*buffer)[read_size - 1] == '\n')
{
(*buffer)[read_size - 1] = '\0'; /* remove trailing newline */
read_size--;
}
info->linecount_flag = 1;
remove_comments(*buffer);
build_history_list(info, *buffer, info->histcount++);
/* if (_strchr(*buffer, ';')) is this a command chain? */
{
*buffer_size = read_size;
info->cmd_buf = buffer;
}
}
}
return (read_size);
}

/**
* get_input_line - gets a line minus the newline
* @info: parameter struct
*
* Return: bytes read
*/
ssize_t get_input_line(info_t *info)
{
static char *buffer; /* the ';' command chain buffer */
static size_t buffer_index, buffer_size;
ssize_t read_size = 0;
char **buffer_pointer = &(info->arg), *current_position;

_putchar(BUF_FLUSH);
read_size = buffer_input(info, &buffer, &buffer_size);
if (read_size == -1) /* EOF */
return (-1);
if (buffer_size) /* we have commands left in the chain buffer */
{
buffer_index = buffer_index;
current_position = buffer + buffer_index;

check_chain(info, buffer, &buffer_index, buffer_index, buffer_size);
while (buffer_index < buffer_size) /* iterate to semicolon or end */
{
if (is_chain(info, buffer, &buffer_index))
break;
buffer_index++;
}

buffer_index = buffer_index + 1;
if (buffer_index >= buffer_size) /* reached end of buffer? */
{
buffer_index = buffer_size = 0; /* reset position and length */
info->cmd_buf_type = CMD_NORM;
}

*buffer_pointer = current_position;
/* pass back pointer to current command position */
return (_strlen(current_position)); /* return length of current command */
}

*buffer_pointer = buffer;
/* else not a chain, pass back buffer from custom_getline() */
return (read_size); /* return length of buffer from custom_getline() */
}

/**
* read_buffer - reads a buffer
* @info: parameter struct
* @buffer: buffer
* @buffer_index: size
*
* Return: read_size
*/
ssize_t read_buffer(info_t *info, char *buffer, size_t *buffer_index)
{
ssize_t read_size = 0;

if (*buffer_index)
return (0);
read_size = read(info->readfd, buffer, READ_BUF_SIZE);
if (read_size >= 0)
*buffer_index = read_size;
return (read_size);
}

/**
* custom_getline - gets the next line of input from STDIN
* @info: parameter struct
* @buffer_ptr: address of pointer to buffer, preallocated or NULL
* @buffer_size: size of preallocated buffer if not NULL
*
* Return: line_size
*/
int custom_getline(info_t *info, char **buffer_ptr, size_t *buffer_size)
{
static char buffer[READ_BUF_SIZE];
static size_t buffer_index, buffer_length;
size_t current_length;
ssize_t read_size = 0, line_size = 0;
char *current_position = NULL, *new_position = NULL, *character;

current_position = *buffer_ptr;
if (current_position && buffer_size)
line_size = *buffer_size;
if (buffer_index == buffer_length)
buffer_index = buffer_length = 0;

read_size = read_buffer(info, buffer, &buffer_length);
if (read_size == -1 || (read_size == 0 && buffer_length == 0))
return (-1);

character = _strchr(buffer + buffer_index, '\n');
current_length = character ?
1 + (unsigned int)(character - buffer) : buffer_length;
new_position = _realloc(current_position, line_size, line_size ?
line_size + current_length : current_length + 1);
if (!new_position) /* MALLOC FAILURE! */
return (current_position ? free(current_position), -1 : -1);

if (line_size)
_strncat(new_position, buffer + buffer_index, current_length - buffer_index);
else
_strncpy(new_position, buffer + buffer_index,
current_length - buffer_index + 1);

line_size += current_length - buffer_index;
buffer_index = current_length;
current_position = new_position;

if (buffer_size)
*buffer_size = line_size;
*buffer_ptr = current_position;
return (line_size);
}

/**
* sigint_handler - blocks ctrl-C
* @signal_number: the signal number
*
* Return: void
*/
void sigint_handler(__attribute__((unused))int signal_number)
{
_puts("\n");
_puts("$ ");
_putchar(BUF_FLUSH);
}

