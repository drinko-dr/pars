//
// Created by Leto Vania on 20/09/2019.
//

#ifndef FILLIT_H
# define FILLIT_H

#include "libft/libft.h"
typedef struct			s_termito
{
	char 				alpha;
	int					*position;
	struct s_termito	*next;
}						t_termito;

typedef struct			s_shape
{
	char				letter;
	int					coord[8];
	struct s_shape		*next;
}						t_shape;

void					parser(char **file, t_shape **shape);
void 					map_del(int **map);
int 					check_place (int **map, t_shape *tetramino, int x, int y, int size);
void 					tetramino_set(int **map, t_shape *tetramino, int x, int y);
void					tetramino_unset(int **map, t_shape *tetramino, int x, int y);
int 					check_tetramino(char *str, int ret);
void					save_coord(char *tetra, t_shape **shape , int count);
void					move_shape(t_shape **shape);
int						read_shape(char *buf, int ret, t_shape **shape, int count);
void					del_list(t_shape **shape);
t_shape					*creat_new_list(void);
int 					**map_create(int size);
int						**map_fill_zero(void);
void 					map_change_to_letter(int **map, int size);



#endif //FILLIT_FILLIT_H
