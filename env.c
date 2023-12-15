/* vim: set noet ts=8 sw=8: */
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include "main.h"


/**
* _getenv - get an environment variable by name
* @name: the name of the variable
* @env: the environment variables
* Return: the value if found or NULL
*/
char *_getenv(const char *name, char **env)
{
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
* _setenv - set an environment variable
* @name: the name of the variable
* @value: the value to set
* @env: the environment variables
* Return: status code
*/
int _setenv(const char *name, const char *value, char **env)
{
	int i = 0, r, d;
	char *e;

	r = strlen(name);
	while (env[i])
	{
		d = findchar(env[i], '=');
		d = (r > d) ? r : d;
		if (strncmp(env[i], name, d) == 0)
			break;
		i++;
	}
	if (env[i] == NULL)
		env[i + 1] = NULL;

	e = calloc(strlen(name) + strlen(value) + 2, sizeof(char));
	free(env[i]);
	env[i] = e;
	strcpy(e, name);
	strcat(e, "=");
	strcat(e, value);

	return (0);
}

/**
* _unsetenv - unset an environment variable
* @name: the name of the variable
* @env: the environment variables
* Return: status code
*/
int _unsetenv(const char *name, char **env)
{
	int i = 0, r, d;
	short found = 0;

	r = strlen(name);
	while (env[i])
	{
		d = findchar(env[i], '=');
		d = (r > d) ? r : d;
		if (found)
			env[i] = env[i + 1];
		else if (strncmp(env[i], name, d) == 0)
		{
			found = 1;
			free(env[i]);
			env[i] = env[i + 1];
		}
		i++;
	}
	return (0);
}

/**
* _getexec - search for executable file in PATH
* @file: the name of the file
* @env: the environment variables
* Return: the value if found or NULL
*/
char *_getexec(char *file, char **env)
{
	char *path, **paths;
	char *tmp = NULL;
	int i;
	struct stat st;

	if (isabs(file))
	{
		if (stat(file, &st) == 0)
			return (file);
		return (NULL);
	}

	path = _getenv("PATH", env);
	if (path == NULL)
		return (NULL);
	path = strdup(path);
	paths = (char **) malloc((_strlen(path) + 1) * sizeof(char *));
	tmp = (char *) malloc((_strlen(path) + _strlen(file) + 2) * sizeof(char));
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
* @env: the environment variables
* Return: void
*/
void printenv(char **env)
{
	int i = 0;

	while (env[i])
	{
		_puts(env[i++]);
		_puts("\n");
	}
}
