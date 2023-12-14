#include "main.h"

int status = 0;
char *string;
char *input = NULL;
/**
 * main - Simple shell program that reads input from the user.
 * @argc: The number of command-line arguments.
 * @argv: An array containing the command-line arguments.
 * @env: The environment variables.
 * Return: The exit status of the shell program.
*/
int main(int argc __attribute__((unused)), char *argv[], char **env)
{
	int token_count;
	char *input_tokens[MAX_TOKENS];
	char *path = NULL;
	char *tokenize;
	char *shell_name;
	size_t size = 0;

	while (1)
	{
		write(STDOUT_FILENO, "", 0);

		shell_name = argv[0];
		if (getline(&input, &size, stdin) == -1)
		{
			free(input);
			exit(status);
		}

		token_count = 0;
		tokenize = strtok(input, " \n;");
		while (tokenize != NULL && token_count < MAX_TOKENS - 1)
		{
			input_tokens[token_count] = tokenize;
			tokenize = strtok(NULL, " \n;");
			token_count++;
		}
		input_tokens[token_count] = NULL;

		if (token_count > 0)
		{
			if (exit_comand(input_tokens, shell_name))
				break;
			if (print_env(input_tokens[0]))
				print_env2(env);

			else if (_strcmp(input_tokens[0], "exit"))
			{
				if (!isFullPath(input_tokens[0]))
				{
					path = stenvp(env);
					execfullpath(path, input_tokens, shell_name);
						free(path);
				}
				else
				{
					one_word_command(input_tokens, shell_name);
				}
			}
		}
	}
	free(string);
	free(input);
	return (status);
}
/**
 * _getline - Reads a line from standard input and stores it in a dynamically
 * @input: A pointer to a char pointer where the input line will be stored.
 * Return: 0 on success, -1 on failure or end-of-file.
*/
int _getline(char **input)
{
	ssize_t r;
	int i;

	string = malloc(10000000);
	if (string == NULL)
		return (-1);

	i = 0;
	while (1)
	{
		r = read(0, (string + i), 1);
		if (r == 0)
			return (-1);
		else
		{
			if (*(string + i) == '\n' || *(string + i) == ';')
			{
				*(string + i + 1) = '\0';
				break;
			}
		}
		i++;
	}
	*input = string;
	return (0);
}
/**
 * print_env2 - Prints the environment variables to standard output.
 * @env: An array of strings representing the environment variables.
*/
void print_env2(char **env)
{
	int i = 0;

	while (env[i] != NULL)
	{
		write(1, env[i], _strlen(env[i]));
		write(1, "\n", 1);
		i++;
	}
}
/**
 * print_env - Checks if the given string represents the "env" command.
 * @string: The input string to be checked.
 * Return: 1 if the string represents the "env" command, 0 otherwise.
 */
int print_env(const char *string)
{
	const char ar[] = "env";
	int i = 0, j = 0;

	while (string[i] != '\0')
	{
		if (string[i] == ar[0])
		{
			j = 0;
			while (ar[j] != '\0' && string[i] == ar[j]) {
				i++;
				j++;
			}
			if (ar[j] == '\0')
			{
				return(1);
			}
		}
		else
			i++;
	}
	return (0);
}
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
					if (arg < 0)
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
