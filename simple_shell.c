#include "main.h"

int status = 0;
char *string;

int _getline(char **input);
int main(int argc __attribute__((unused)), char *argv[], char **env)
{
	int token_count;
	char *input_tokens[MAX_TOKENS];
	char *path = NULL;
	char *tokenize;
	char *shell_name;
	char *input = NULL;

	while (1)
	{
		write(STDOUT_FILENO, "", 0);

		shell_name = argv[0];
		if (_getline(&input) == -1)
		{
			free(string);
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
			if (exit_comand(input_tokens))
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

int exit_comand(char **input_tokens)
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
						write(2, "./hsh", 5);
						write(2, ": 1: exit: Illegal number: ", 27);
						write(2, input_tokens[1], _strlen(input_tokens[1]));
						write(2, "\n", 1);
						status = 2;
					}
					else
					{
						exit(arg);
					}
				}
				else
				{
					write(2, "$: exit doesn't take more than one argument\n", 44);
				}
			}
		}
		i++;
	}
	return (0);
}

int isFullPath(const char *string)
{
	const char ar[] = "/";
	int i = 0, j = 0;

	while (string[i] != '\0') {
		if (string[i] == ar[0]) {
			j = 0;
			while (ar[j] != '\0' && string[i] == ar[j]) {
				i++;
				j++;
			}
			if (ar[j] == '\0') {
				return (1);
			}
		}
		i++;
	}
	return (0);
}
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
