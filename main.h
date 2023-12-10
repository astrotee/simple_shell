#ifndef MAIN_H
#define MAIN_H
#include <stddef.h>




size_t _strlen(char *str);
int _puts(char *str);
int tokenize(char *str, char **lst);
int getcmd(char *cmd, char **args);
int interactive(char **argv, char **env);
int script(char **argv, char **env);

#endif
