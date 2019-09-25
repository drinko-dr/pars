//
// Created by Leto Vania on 19/09/2019.
//

#include <stdio.h>
#include "fillit.h"
#include <stdlib.h>
#include <fcntl.h>
// void print_shape(int **map, int size)
// 	{
// 		int i,j;
// 		i = j = 0;
// 		while (i < size)
// 		{
// 			j = 0;
// 			while (j < size)
// 			{
// 				if (map[i][j] == 0)
// 					printf(".");
// 				else
// 					printf("%c", map[i][j]);
// 				j++;
// 			}
// 			printf("\n");
// 			i++;
// 		}
// 	}

int     main(int argc, char *argv[])
{
	if (argc == 1)
		return (0);
	t_shape	*shape;
	t_shape	*head_shape;
	shape = creat_new_list();
	head_shape = shape;
	int size;
	int count;
	count = parser(&argv[1], &shape);
	if (count == 0)
		return (0);
	int		**map;
	//  = map_create(104);
	map = map_fill_zero();
	count *= 4;
	size = ft_sqrt(count);
	// if (count < 44)
	// 	size -= 1;
	while(!solver(map, head_shape, size))
    {
        size++;
        //free(map);
        // map = map_fill_zero();
    }
	// solver(map, head, 3);
	print_shape(map, size);
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
