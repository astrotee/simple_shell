#ifndef MAIN_H
#define MAIN_H
#include <stddef.h>




size_t _strlen(const char *str);
int _puts(const char *str);
int findchar(const char *str, char c);
int _strcmp(const char *str1, const char *str2);


int tokenize(char *str, char **lst, char *delim);
short isabs(char *path);
void _perr(char *cmd, int line, char *errmsg, ...);

char *_getenv(const char *name, char **env);
int _setenv(const char *name, const char *value, char **env);
void printenv(char **env);
char *_getexec(char *file, char **env);


int bi_exit(char *cmd, int line, char **args, int status);
int builtin(char *cmd, char **env, int line, char **args, int status);

int getcmd(char **cmd, char ***args);
int forkexec(char *path, char **args, char **env);
int start(char **args, char **env);

#endif
