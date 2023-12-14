/* vim: set noet ts=8 sw=8: */
#include <stddef.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include "main.h"


/**
* builtin - run builtin command if it is
* @cmd: cmd name
* @args: command args
* @status: the last exit code
* Return: status code
*/
int builtin(char *cmd, char **args, int status)
{
	int e;

	if (_strcmp(args[0], "exit") == 0)
	{
		if (args[1])
		{
			e = atoi(args[1]);
			if (e == 0)
				return (2);
		}
		else
			e = status;
		free(cmd);
		free(args);
		exit(e);
	}
	if (_strcmp(args[0], "env") == 0)
	{
		printenv();
		return (0);
	}
	return (-1);
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
	*args = (char **)malloc((nread + 1) * sizeof(char *));
	tokenize(*cmd, *args, " ");
	return (0);
}

/**
* forkexec - fork and execute command
* @path: path to executable
* @args: arguments array
* Return: status code
*/
int forkexec(char *path, char **args)
{
	int status;
	pid_t pid;

	pid = fork();
	if (pid == -1)
		return (-1);
	if (pid == 0)
	{
		execve(path, args, environ);
		return (1);
	}
	wait(&status);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (status);
}

/**
* start - Start interactive shell
* @argv: the args values
* Return: status code
*/
int start(char **argv)
{
	int status = 0, line = 1;
	char *cmd = NULL, **args = NULL, *path;
	short interactive = isatty(STDIN_FILENO);

	do {
		if (interactive)
			_puts("$ ");
		if (getcmd(&cmd, &args) < 0)
			exit(EXIT_SUCCESS);
		if (args[0] == NULL)
			goto end;
		status = builtin(cmd, args, status);
		if (status == 2)
			_perr(interactive, argv[0], args, line, 2);
		if (status != -1)
			goto end;
		path = _getexec(args[0]);
		if (path == NULL)
		{
			status = 127;
			_perr(interactive, argv[0], args, line, 127);
			goto end;
		}
		status = forkexec(path, args);
		if (isabs(args[0]) == 0)
			free(path);
end:
		free(cmd);
		free(args);
		if (status && interactive == 0)
			exit(status);
		line++;
	} while (1);
	return (status);
}

/**
* main - Run the shell
* @argc: the args count
* @argv: the args values
* @env: the environment variables
* Return: the exit status
*/
int main(int argc, char **argv, char **env)
{

	if (argc > 1)
		execve(*argv, argv, env);
	start(argv);
	return (0);
}
