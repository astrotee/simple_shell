/* vim: set noet ts=8 sw=8: */
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "main.h"


/**
* builtin - run builtin command if it is
* @cmd: the shell command
* @env: the environment variables
* @line: the current line number
* @args: command args
* @status: the last exit status
* Return: status code
*/
int builtin(char *cmd, char **env, int line, char **args, int status)
{

	if (_strcmp(args[0], "exit") == 0)
		return (bi_exit(cmd, line, args, status));
	if (_strcmp(args[0], "env") == 0)
	{
		printenv(env);
		return (0);
	}
	if (_strcmp(args[0], "setenv") == 0)
	{
		if (args[1] && args[2])
		{
			_setenv(args[1], args[2], env);
			return (0);
		}
		_perr(cmd, line, "missing arguments!");
		return (1);
	}
	if (_strcmp(args[0], "setenv") == 0)
	{
		if (args[1])
		{
			unsetenv(args[1]);
			return (0);
		}
		_perr(cmd, line, "missing arguments!");
		return (1);
	}
	return (-1);
}

/**
* bi_exit - builtin exit command
* @cmd: the shell command
* @line: the current line number
* @args: command args
* @status: the last exit status
* Return: status code
*/
int bi_exit(char *cmd, int line, char **args, int status)
{
	int e;

	if (args[1])
	{
		e = atoi(args[1]);
		if (e <= 0)
		{
			_perr(cmd, line, "%s: Illegal number: %s", args[0], args[1]);
			return (2);
		}
	}
	else
		e = status;
	free(args);
	exit(e);

}
