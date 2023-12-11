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
* start - Start interactive shell
* @argv: the args values
* @env: environment variables
* Return: status code
*/
int start(char **argv, char **env)
{
	int status;
	pid_t pid;
	char *cmd = NULL, **args = NULL;
	short interactive = isatty(STDIN_FILENO);

	do {
		if (interactive)
			_puts("$ ");
		if (getcmd(&cmd, &args) < 0)
			return (0);
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
			execve(*args, args, env);
			perror(argv[0]);
			free(cmd);
			free(args);
			exit(EXIT_FAILURE);
		} else
			wait(&status);
		free(cmd);
		free(args);
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
	start(argv, env);
	return (0);
}
