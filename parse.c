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

