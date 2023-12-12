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

#define MAX_TOKENS 50
#define MAX_PATH_LENGTH 256

int _getline(char **input);
int isFullPath(const char *string);
void cleanup(char *input, char *path);
void execfullpath(char *path, char *input_tokens[], char *shell_name);
char *stenvp(char *envp[]);
void one_word_command(char *input_tokens[], char *shell_name);
int exit_comand(char **input_tokens);
int print_env(const char *string);
void print_env2(char **env);
char **_strtok(char *input);

#endif /*SIMPLE_SHELL*/