/* vim: set noet ts=8 sw=8: */
#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include "main.h"


/**
* isabs - check if path is absolute
* @path: the path string
* Return: 1 if True
*/
short isabs(char *path)
{
	if (findchar(path, '/') == -1)
		return (0);
	return (1);
}

/**
* tokenize - split string by delimiter
* @str: the string
* @lst: the split string
* @delim: the delimiter
* Return: the status code
*/
int tokenize(char *str, char **lst, char *delim)
{
	char *token, *str1;
	size_t lastchar, i = 0;

	for (i = 0, str1 = str; ; i++, str1 = NULL)
	{
		token = strtok(str1, delim);
		lst[i] = token;
		if (token == NULL)
			break;
		lastchar = _strlen(token) - 1;
		if (token[lastchar] == '\n')
		{
			token[lastchar] = '\0';
			lst[i + 1] = NULL;
			break;
		}
	}
	return (0);
}
/**
* _perr - print error string
* @i: ineractive
* @cmd: command name
* @args: arguments
* @line: line number
* @errc: error code
* Return: void
*/
void _perr(short i, const char *cmd, char **args, int line, int errc)
{

	fprintf(stderr, "%s: ", cmd);
	if (i == 0)
		fprintf(stderr, "line %d: ", line);
	switch (errc)
	{
		case 2:
			fprintf(stderr, "%s: %s: numeric argument required\n",
					args[0], args[1]);
		break;
		case 127:
			fprintf(stderr, "%s: ", args[0]);
			perror("");
	}
}

