#include "fillit.h"

void print_shape(int **map, int size)
	{
		int i,j;
		i = j = 0;
		while (i < size)
		{
			j = 0;
			while (j < size)
			{
				if (map[i][j] == 0)
					printf(".");
				else
					printf("%c", map[i][j]);
				j++;
			}
			printf("\n");
			i++;
		}
	}
