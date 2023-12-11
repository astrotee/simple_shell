/* vim: set noet ts=8 sw=8: */
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>


/**
* _strlen - count the chars in a string
* @str: the string
* Return: the length of the string
*/
size_t _strlen(char *str)
{
	size_t i = 0;

	while (str[i++])
		;

	return (--i);
}

/**
* _puts - print a null terminated string
* @str: the string
* Return: the status code
*/
int _puts(char *str)
{
	int i;

	i = _strlen(str);
	if (i == 0)
		return (-1);

	if (write(STDOUT_FILENO, str, i) < i)
		return (-1);

	return (0);
}

/**
* tokenize - split string by spaces
* @str: the string
* @lst: the split string
* Return: the status code
*/
int tokenize(char *str, char **lst)
{
	char *token, *str1;
	size_t lastchar, i = 0;

	for (i = 0, str1 = str; ; i++, str1 = NULL)
	{
		token = strtok(str1, " ");
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
* getcmd - get input command line
* @cmd: pointer to line read
* @args: the parsed args
* Return: status code
*/

int getcmd(char **cmd, char ***args)
{
	size_t len = 0;
	ssize_t nread;

	nread = getline(cmd, &len, stdin);
	if (nread == -1)
	{
		free(*cmd);
		return (-1);
	}
	(*cmd)[nread - 1] = '\0';
	*args = (char **)malloc(nread * sizeof(char));
	tokenize(*cmd, *args);
	return (0);
}
