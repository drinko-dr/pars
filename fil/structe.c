#include "libft/libft.h"
#include "fillit.h"

t_shape		*creat_new_list(void)
{
	t_shape		*node;

	if (!(node = (t_shape *)malloc(sizeof(t_shape))))
		return (NULL);
	node->next = NULL;
	return (node);
}

void		del_list(t_shape **shape)
{
	if (*shape && (*shape)->next)
		del_list(&(*shape)->next);
	free(*shape);
	*shape = NULL;
}

int		read_shape(char *buf, int ret, t_shape **shape, int count)
{
	if(!check_tetramino(buf,ret))
		return (0);
	else
	{
		save_coord(buf, shape, count);
		move_shape(shape);
		(*shape)->next = creat_new_list();
		*shape = (*shape)->next;
	}
	return (1);
}