/* vim: set noet ts=8 sw=8: */
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>


/**
* _strcmp - find the index of a char
* @str1: 1st string
* @str2: 2nd string
* Return: 0 if equal
*/
int _strcmp(const char *str1, const char *str2)
{
	int i = 0;

	while (str1[i])
	{
		if (str1[i] > str2[i])
			return (1);
		else if (str1[i] < str2[i])
			return (-1);
		if (str1[i] != 0 || str2[i] != 0)
			return (0);
		i++;
	}
	return (str1[i] - str2[i]);
}


/**
* findchar - find the index of a char
* @str: the string to search
* @c: the character to look for
* Return: the index or -1 if not found
*/
int findchar(const char *str, char c)
{
	int i = 0;

	while (str[i])
	{
		if (str[i] == c)
			return (i);
		i++;
	}

	return (-1);
}


/**
* _strlen - count the chars in a string
* @str: the string
* Return: the length of the string
*/
size_t _strlen(const char *str)
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
int _puts(const char *str)
{
	int i;

	i = _strlen(str);
	if (i == 0)
		return (-1);

	if (write(STDOUT_FILENO, str, i) < i)
		return (-1);

	return (0);
}

