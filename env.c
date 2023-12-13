/* vim: set noet ts=8 sw=8: */
#include "main.h"
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>


/**
* _getenv - get an environment variable by name
* @name: the name of the variable
* Return: the value if found or NULL
*/
char *_getenv(const char *name)
{
	char **env = environ;
	int i = 0, len1, len2;

	len1 = _strlen(name);
	while (env[i])
	{
		len2 = findchar(env[i], '=');
		if (len1 == len2 && _strcmp(name, env[i]) == 0)
			return (&env[i][len2 + 1]);
		i++;
	}

	return (NULL);
}

/**
* _getexec - search for executable file in PATH
* @file: the name of the file
* Return: the value if found or NULL
*/
char *_getexec(const char *file)
{
	char *path, **paths;
	char *tmp = NULL;
	int i;
	struct stat st;

	path = _getenv("PATH");
	if (path == NULL)
		return (NULL);
	path = strdup(path);
	paths = (char **) malloc(_strlen(path) * sizeof(char));
	tmp = (char *) malloc(_strlen(path) * sizeof(char));
	tokenize(path, paths, ":");
	for (i = 0; paths[i]; i++)
	{
		strcpy(tmp, paths[i]);
		strcat(tmp, "/");
		strcat(tmp, file);
		if (stat(tmp, &st) == 0)
		{
			free(path);
			free(paths);
			return (tmp);
		}
	}
	free(path);
	free(paths);
	free(tmp);

	return (NULL);
}

/**
* printenv - print environment variables
* Return: void
*/
void printenv(void)
{
	int i = 0;

	while (environ[i])
	{
		_puts(environ[i++]);
		_puts("\n");
	}
}
