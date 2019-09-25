//
// Created by Leto Vania on 20/09/2019.
//

#include "fillit.h"

int 	solver(int **map, t_shape *tet, int size)
{
	int 	row;
	int		col;

	row = 0;
	col = 0;
	if (tet->coord[7] == ((size * size) - 1) || tet->coord[6] == ((size * size) - 2))
		return (0);
	if (tet->next)
	{
		while (col < size) // заменить на start_row
		{
			row = 0;
			while (row < size) // заменит start_col
			{
				if (check_place(map, tet, row, col, size)) {
					tetramino_set(map, tet, row, col);
					if (solver(map, tet->next, size))
						return (1);
					tetramino_unset(map, tet, row, col);
				}
				row++;
			}
			col++;
		}
	}
	if (tet->next)
		return (0);
	return (1); // что нужно вернуть ?
}


// для квадрата размером size_square
// для каждой i,j ячейки попробовать установить фигуру
// 		если фигура выходит за границы квадрата или наезжает на другую фигуру сдвинуть фигуру ввправо
//		если не получается сдвинуть вправо сдвинуть вниз
//	повторять пока первая фигура не окажеться в правом верхнем углу
//		если отсутствует площадь куда можно поставить фигуру, увеличение размера квадрата и начать сначала
//
