#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_WORDS 50

char **_strtok(char *input)
{
	int i = 0, j = 0, d = 0;
	char **string = malloc(MAX_WORDS * sizeof(char *));

	if (string == NULL) {
		perror("malloc failed");
		exit(EXIT_FAILURE);
	}

	string[j] = malloc(strlen(input) + 1);

	if (string[j] == NULL) {
		perror("malloc failed");
		exit(EXIT_FAILURE);
	}

	for (i = 0; input[i] != '\0'; i++, d++) {
		if (input[i] != ' ' && input[i] != '\n' && input[i] != ';') {
			string[j][d] = input[i];
		} else {
			string[j][d] = '\0';
			d = -1;
			j++;
			string[j] = malloc(strlen(input) + 1);

			if (string[j] == NULL) {
				perror("malloc failed");
				exit(EXIT_FAILURE);
			}
		}
	}
	if (j == 0 && d == 0) {
		string[j][d] = '\0';
		j++;
	}
	string[j] = NULL;
	return string;
}
