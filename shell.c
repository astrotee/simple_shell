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
* script - execute a script
* @argv: the args values
* @env: environment variables
* Return: status code
*/
int script(char **argv, char **env)
{
	int status;
	pid_t pid;
	char *cmd = NULL, **args = NULL;

	args = (char **)malloc(1024 * sizeof(char));

	while (getcmd(cmd, args) == 0)
	{
		pid = fork();
		if (pid == -1)
		{
			perror(argv[0]);
			free(cmd);
			free(args);
			return (-1);
		}
		if (pid == 0)
		{
			if (execve(*args, args, env) < 0)
			{
				perror(argv[0]);
				free(cmd);
				free(args);
				return (-1);
			}
		} else
			wait(&status);
	}
	free(cmd);
	free(args);
	return (0);
}

/**
* interactive - Start interactive shell
* @argv: the args values
* @env: environment variables
* Return: status code
*/
int interactive(char **argv, char **env)
{
	int status;
	pid_t pid;
	char *cmd = NULL, **args = NULL;

	args = (char **)malloc(1024 * sizeof(char));

	do {
		_puts("$ ");
		if (getcmd(cmd, args) < 0)
			return (-1);
		pid = fork();
		if (pid == -1)
		{
			perror(argv[0]);
			free(cmd);
			free(args);
			return (-1);
		}
		if (pid == 0)
		{
			if (execve(*args, args, env) < 0)
			{
				perror(argv[0]);
				free(cmd);
				free(args);
				return (-1);
			}
		} else
			wait(&status);
	} while (1);
	free(cmd);
	free(args);
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
	if (isatty(STDIN_FILENO))
		interactive(argv, env);
	else
		script(argv, env);
	return (0);
}
