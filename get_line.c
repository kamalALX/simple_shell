#include "main.h"

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
