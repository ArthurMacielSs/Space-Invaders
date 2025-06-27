#include <stdio.h>
#include <stdlib.h>
#include "invaders.h"

int alloca_alien(int rows, int cols, Alien ***alien)
{
	*alien = (Alien **)malloc(rows * sizeof(Alien *));
	if (*alien == NULL)
	{
		return 0;
	}

	for (int i = 0; i < rows; i++)
	{
		(*alien)[i] = (Alien *)malloc(cols * sizeof(Alien));

		if ((*alien)[i] == NULL)
		{
			for (int j = 0; j < i; j++)
			{
				free((*alien)[j]);
			}
			free(*alien);
			*alien = NULL;
			return 0;
		}
	}

	return 1;
}

int free_alien(int rows, Alien ***alien)
{
	if (*alien == NULL)
	{
		return 1;
	}

	for (int i = 0; i < rows; i++)
	{
		free((*alien)[i]);
	}

	free(*alien);
	*alien = NULL;
	return 1;
}