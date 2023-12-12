#include "main.h"

/**
 *  * _strcmp -  a function that compares two strings.
 *   *
 *    * @s1: input
 *     * @s2: input
 *      *
 *       * Return: return the comparison
 *       */

int _strcmp(char *s1, char *s2)
{
	int i;

	for (i = 0; s1[i] != '\0' && s2[i] != '\0'; i++)
	{
		if (s1[i] != s2[i])
		{
			return (s1[i] - s2[i]);
		}
	}
	return (s1[i] - s2[i]);
}

#include<stdio.h>

/**
 *  * _atoi -  a function that convert a string to an integer.
 *   *
 *    * @s: input
 *     *
 *      * Return: 0 success
 *      */

int _atoi(char *s)
{
	int sign = 1;
	int sum = 0;
	int i = 0;

	while (s[i] != '\0')
	{
		if (s[i] == '-')
			sign = sign * -1;
		else if (s[i] >= '0' && s[i] <= '9')
			sum = (sum * 10) + (s[i] - '0');
		else if (sum > 0)
			break;
		i++;
	}
	return (sum * sign);
}

#include "main.h"

/**
 *  * *_strcat - append two strings.
 *   *
 *    * @dest: input.
 *     * @src: inout.
 *      *
 *       * Return: a pointer to the resulting string dest.
 *       */

char *_strcat(char *dest, char *src)
{
	char *result = malloc(sizeof(char) * (strlen(dest) + strlen(src) + 1));

	if (result == NULL) {
		return NULL;
	}

	strcpy(result, dest);
	strcpy(result + strlen(dest), src);

	return (result);
}
