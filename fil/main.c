//
// Created by Leto Vania on 19/09/2019.
//

#include <stdio.h>
#include "fillit.h"
#include <stdlib.h>
#include <fcntl.h>
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

int     main(int argc, char *argv[])
{
	if (argc == 1)
		return (0);
	t_shape	*shape;
	t_shape	*head;
	shape = creat_new_list();
	head = shape;
	int size = parser(&argv[1], &shape);
	int		**map;
	//  = map_create(104);
	map = map_fill_zero();


	while (size < 20)
	{
		if (solver(map, head, size))
			break ;
		size++;
	}
	// solver(map, head, 3);
	print_shape(map, size + 1);
	// int i, j;
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

	// int row, col;
	// row = col = 0;
	// char k;
	// while (head)
	// {
	// 	while (row < 10) // заменить на start_row
	// 	{
	// 		col = 0;
	// 		while (col < 10) // заменит start_col
	// 		{
	// 			if (check_place(map, head, row, col, 10))
	// 			{
	// 				tetramino_set(map, head, row, col);
	// 				i = j = 0;
	// 				print_shape(map);
	// 				head  = head->next;
	// 			}
	// 			col++;
	// 		}
	// 		row++;
	// 	}
	// 	head  = head->next;
	// }


	return (0);

}
