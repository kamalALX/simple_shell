#include "main.h"
/**
 * _getline - Reads a line from standard input and stores it in a dynamically.
 * @input: A pointer to a char pointer where the input line will be stored.
 * Return: 0 on success, -1 on failure or end-of-file.
 */
int _getline(char **input)
{
	ssize_t r;
	int i;
	char *string;

	string = malloc(10000000);
	if (string == NULL)
		return (-1);

	i = 0;
	while (1)
	{
		r = read(0, (string + i), 1);
		if (r == 0)
			return (-1);
		if (*(string + i) == '\n' || *(string + i) == ';')
		{
			*(string + i + 1) = '\0';
			break;
		}
		i++;
	}
	*input = string;
	return (0);
}
