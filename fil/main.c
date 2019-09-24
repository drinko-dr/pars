//
// Created by Leto Vania on 19/09/2019.
//

#include "libft/libft.h"
#include <stdio.h>
#include "fillit.h"
#include <stdlib.h>
#include <fcntl.h>

int     main(int argc, char *argv[])
{
	if (argc == 1)
		return (0);
	t_shape	*shape;
	t_shape	*head;
	shape = creat_new_list();
	head = shape;
	parser(&argv[1], &shape);
	int		**map;
	//  = map_create(104);
	map = map_fill_zero();
	int i, j;
	// i = j = 0;
	// while (i < 104)
	// {
	// 	j = 0;
	// 	while (j < 104)
	// 	{
	// 		printf("%d", map[i][j]);
	// 		j++;
	// 	}
	// 	i++;
	// }

	// tetramino_set(map, head, 0, 0);
	// tetramino_set(map, head->next->next->next->next->next, 0, 1);
	// if (check_place(map, head, 0, 0, 10))
	// {
	// 	tetramino_set(map, head, 0, 0);
	// }
	// if (check_place(map, head, 2, 2, 5))
	// {
	// 	tetramino_set(map, head, 2, 2);
	// }
	// tetramino_unset(map,head->next->next->next->next->next, 0, 1);
	int row, col;
	row = col = 0;
	char k;
	while (head->letter)
	{
		while (row < 10) // заменить на start_row
		{
			col = 0;
			while (col < 10) // заменит start_col
			{
				if (check_place(map, head, row, col, 10)) 
				{
					tetramino_set(map, head, row, col);
					i = j = 0;
					while (i < 10)
					{
						j = 0;
						while (j < 10)
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
					head  = head->next;
					if (!head)
						break ;	
				}
				col++;
				if (!head)
					break ;
			}
			row++;
			if (!head)
				break ;
		}
		if (!head)
			break ;
	}

	
	return (0);

}
