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
	return (0);
}

/**
* start - Start interactive shell
* @argv: the args values
* Return: status code
*/
int start(char **argv)
{
	int status;
	char *cmd = NULL, **args = NULL, *path;
	short interactive = isatty(STDIN_FILENO);

	do {
		if (interactive)
			_puts("$ ");
		if (getcmd(&cmd, &args) < 0)
			exit(EXIT_SUCCESS);
		if (args[0] == NULL)
		{
			free(cmd);
			free(args);
			continue;
		}
		path = isabs(args[0]) ? args[0] : _getexec(args[0]);
		if (path == NULL)
		{
			perror(argv[0]);
			free(cmd);
			free(args);
			continue;
		}
		status = forkexec(path, args);
		if (isabs(args[0]) == 0)
			free(path);
		free(cmd);
		free(args);
		if (status)
			perror(argv[0]);
		if (status == 1)
			exit(EXIT_FAILURE);
	} while (1);
	return (0);
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
