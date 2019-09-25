//
// Created by Leto Vania on 19/09/2019.
//

#include "fillit.h"
#include <stdio.h>


void	move_shape(t_shape **shape)
{
	int i;
	int y;
	int j;
	int x;

	x = (*shape)->coord[0];
	y = (*shape)->coord[1];
	i = 0;
	j = 1;
	while (i < 8)
	{
		(*shape)->coord[j] -= y;
		if ((*shape)->coord[i] < x)
			x = (*shape)->coord[i];
		j += 2;
		i += 2;
	}
	j = 0;
	while (j < 8)
	{
		(*shape)->coord[j] -= x;
		j += 2;
	}
}

void		save_coord(char *tetra, t_shape **shape , int count)
{
	int		tag;
	int		i;

	tag = 1;
	i = 0;
	while (i < 20)
	{
		if (tetra[i] == '\n')
			i++;
		if (tetra[i] == '#')
		{
			(*shape)->coord[tag - 1] = i / 5;
			(*shape)->coord[tag] = i % 5;
			tag += 2;
		}
		i++;
	}
	(*shape)->letter = 'A' + count;
}

int check_tetramino(char *str, int ret)
{
	int		tag;
	int 	i;

	i = 0;
	tag = 0;
	while (i < 21) {
		if (i % 5 < 4) {
			if (!(str[i] == '.' || str[i] == '#') && i != 20)
				return (0);
			if (str[i] == '#' && ++tag > 4)
				return (0);
		} else if (str[i] != '\n')
			return (0);
		if (ret == 21 && str[20] != '\n')
			return (0);
		i++;
	}
	return (1);
}

int		parser(char **file, t_shape **shape)
{
	char 	*buf;
	int 	fd;
	int 	ret;
	int		count;

	count = 0;
	buf = (char*)malloc(sizeof(char)*21);
	fd = open(*file, O_RDONLY);
	while((ret = read(fd, buf, 21)) >= 20)
	{
		buf[ret] = '\0';
		if (!read_shape(buf, ret, shape, count))
		{
			printf("error");
			del_list(shape);
			return (0) ;
		}
		count++;
	}
	// free(buf);
	close(fd);
	return (count);
}

