//
// Created by Leto Vania on 20/09/2019.
//

#include "fillit.h"

int 	solver(int start_row, int start_col, t_shape *tet,int size)
{
	int 	row;
	int		col;
	int 	square_size;
	int		**map;

	row = 0;
	col = 0;
	while (tet)
	{
		while (row < square_size) // заменить на start_row
		{
			while (col < square_size) // заменит start_col
			{
				if (check_place(map, tet, col, row, size)) {
					tetramino_set(map, tet, row, col);
					if (solver(row, col, tet->next, size))
						return (1);
					tetramino_unset(map, tet, row, col);
				}
				col++;
			}
			row++;
		}
	}
	return (1); // что нужно вернуть ?
}


// для квадрата размером size_square
// для каждой i,j ячейки попробовать установить фигуру
// 		если фигура выходит за границы квадрата или наезжает на другую фигуру сдвинуть фигуру ввправо
//		если не получается сдвинуть вправо сдвинуть вниз
//	повторять пока первая фигура не окажеться в правом верхнем углу
//		если отсутствует площадь куда можно поставить фигуру, увеличение размера квадрата и начать сначала
//