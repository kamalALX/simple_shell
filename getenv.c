#include "main.h"

char *_custom_getenv(const char *target_name)
{
	char **current_environment;
	char *pair_pointer;
	const char *name_copy;

	for (current_environment = environ; *current_environment != NULL; current_environment++)
	{
		for (pair_pointer = *current_environment, name_copy = target_name;
				*pair_pointer == *name_copy; pair_pointer++, name_copy++)
		{
			if (*pair_pointer == '=')
				break;
		}
		if ((*pair_pointer == '=') && (*name_copy == '\0'))
			return (pair_pointer + 1);
	}

	return (NULL);
}

