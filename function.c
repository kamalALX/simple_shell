#include "main.h"

/**
 * exit_comand - Checks if the given input_tokens represent the exit command.
 * @input_tokens: An array of strings representing the command and its arguments.
 * @shell_name: The name of the shell program.
 * Return: 0.
 */
int exit_comand(char **input_tokens, char *shell_name)
{
	const char ar[] = "exit";
	int i = 0, j = 0, arg;
	char *string = input_tokens[0];

	while (string[i] != '\0')
	{
		if (string[i] == ar[0])
		{
			j = 0;
			while (ar[j] != '\0' && string[i] == ar[j])
			{
				i++;
				j++;
			}
			if (ar[j] == '\0')
			{
				for (i = 0; input_tokens[i] != NULL; i++)
					;
				if (i == 1)
					return (1);
				else if (i == 2)
				{
					arg = _atoi(input_tokens[1]);
					if (arg <= 0)
					{
						write(2, shell_name, _strlen(shell_name));
						write(2, ": 1: exit: Illegal number: ", 27);
						write(2, input_tokens[1], _strlen(input_tokens[1]));
						write(2, "\n", 1);
						status = 2;
						break;
					}
					else
					{
						free(input);
						exit(arg);
					}
				}
				else
				{
					write(2, shell_name, _strlen(shell_name));
					write(2, ": exit: too many arguments\n", 27);
					break;
				}
			}
		}
		i++;
	}
	return (0);
}
/**
 * isFullPath - Checks if the given string represents a full path.
 * @string: The input string to be checked.
 * Return: 1 if the string represents a full path, 0 otherwise.
 */
int isFullPath(const char *string)
{
	const char ar[] = "/";
	int i = 0, j = 0;

	while (string[i] != '\0')
	{
		if (string[i] == ar[0])
		{
			j = 0;
			while (ar[j] != '\0' && string[i] == ar[j])
			{
				i++;
				j++;
			}
			if (ar[j] == '\0')
			{
				return (1);
			}
		}
		i++;
	}
	return (0);
}
/**
 * stenvp - Extracts the value of the "PATH" environment variable.
 * @envp: An array of strings representing the environment variables.
 * Return: A dynamically allocated string containing the value of PATH.
 */
char *stenvp(char *envp[])
{
	char *path;
	const char ar[] = "PATH";
	int i = 0, j = 0, d;

	while (envp[i] != NULL)
	{
		if (envp[i][0] == ar[0])
		{
			j = 0;
			while (ar[j] != '\0' && envp[i][j] == ar[j])
			{
				j++;
			}
			d = 5;
			if (ar[j] == '\0')
			{
				j = 0;
				path = malloc(_strlen(envp[i]) - d + 1);
				if (path == NULL)
					exit(EXIT_FAILURE);
				while (envp[i][d] != '\0')
				{
					path[j] = envp[i][d];
					d++;
					j++;
				}
				path[j] = '\0';
				return (path);
			}
		}
		i++;
	}
	return (NULL);
}

/**
 * execfullpath - Executes a command by searching for it in the specified path.
 * @path: The colon-separated PATH environment variable.
 * @input_tokens: An array of strings representing the command and its arguments.
 * @shell_name: The name of the shell program.
 */
void execfullpath(char *path, char *input_tokens[], char *shell_name)
{
	pid_t pid;
	char *token;
	char *full_path;
	int found = 0;
	char *half_path;

	token = strtok(path, ":");
	while (token != NULL)
	{
		half_path = _strcat(token, "/");
		full_path = _strcat(half_path, input_tokens[0]);
		if (full_path == NULL)
		{
			found = 1;
			break;
		}
		if (access(full_path, X_OK) == 0)
		{
			free(half_path);
			pid = fork();
			if (pid == 0)
			{
				execve(full_path, input_tokens, NULL);
			}
			else
			{
				waitpid(pid, &status, 0);
				free(full_path);
				status >>= 8;
				found = 1;
				break;
			}
		}
		free(half_path);
		free(full_path);
		token = strtok(NULL, ":");
	}
	if (!found)
	{
		write(2, shell_name, _strlen(shell_name));
		write(2, ": 1: ", 5);
		write(2, input_tokens[0], _strlen(input_tokens[0]));
		write(2, ": not found\n", 12);
		status = 127;
	}

}
/**
 * one_word_command - Executes a command with a single word.
 * @input_tokens: An array of strings representing the command and its arguments.
 * @shell_name: The name of the shell program.
 */
void one_word_command(char *input_tokens[], char *shell_name)
{
	pid_t pid;

	if (access(input_tokens[0], X_OK) == 0)
	{
		pid = fork();
		if (pid == 0)
		{
			if (execve(input_tokens[0], input_tokens, NULL) == -1)
			{
				perror(_custom_getenv("PWD"));
				exit(2);
			}
		}
		else
		{
			waitpid(pid, &status, 0);
			status >>= 8;
		}
	}
	else
	{
		write(2, shell_name, _strlen(shell_name));
		write(2, ": 1: ", 5);
		write(2, input_tokens[0], _strlen(input_tokens[0]));
		write(2, ": not found\n", 12);
		status = 127;
	}
}
