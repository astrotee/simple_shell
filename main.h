#ifndef MAIN_H
#define MAIN_H
#include <stddef.h>


extern char **environ;


size_t _strlen(const char *str);
int _puts(const char *str);
int findchar(const char *str, char c);
int _strcmp(const char *str1, const char *str2);


int tokenize(char *str, char **lst, char *delim);
short isabs(char *path);
void _perr(short i, const char *cmd, char **args, int line, int errc);

char *_getenv(const char *name);
void printenv(void);
char *_getexec(char *file);

int getcmd(char **cmd, char ***args);
int forkexec(char *path, char **args);
int builtin(char *cmd, char **args, int status);
int start(char **argv);

#endif
