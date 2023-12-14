#ifndef SIMPLE_SHELL
#define SIMPLE_SHELL

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <limits.h>

extern int status;
extern char *line;
extern char *result;
extern char **environ;
extern char *input;

#define MAX_TOKENS 50
#define MAX_PATH_LENGTH 256

int isFullPath(const char *string);
void execfullpath(char *path, char *input_tokens[], char *shell_name);
char *stenvp(char *envp[]);
void one_word_command(char *input_tokens[], char *shell_name);
int exit_comand(char **input_tokens, char *shell_name);
int print_env(const char *string);
void print_env2(char **env);
char **_strtok(char *input);
int _strcmp(char *s1, char *s2);
int _atoi(char *s);
char *_strcat(char *dest, char *src);
int _strlen(char *s);
char *_custom_getenv(const char *target_name);

#endif /*SIMPLE_SHELL*/
