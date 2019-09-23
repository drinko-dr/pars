//
// Created by Leto Vania on 19/09/2019.
//

#include "libft/libft.h"
#include <stdio.h>
#include "fillit.h"
#include <stdlib.h>
#include <fcntl.h>

void	move_shape(t_shape *shape)
{
	int i;
	int y;
	int j;
	int x;

	x = shape->coord[0];
	y = shape->coord[1];
	i = 0;
	j = 1;
	while (i < 8)
	{
		shape->coord[j] -= y;
		if (shape->coord[i] < x)
			x = shape->coord[i];
		j += 2;
		i += 2;
	}
	j = 0;
	while (j < 8)
	{
		shape->coord[j] -= x;
		j += 2;
	}
}

void		save_coord(char *tetra, t_shape *shape , int count)
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
			shape->coord[tag - 1] = i % 5;
			shape->coord[tag] = i / 5;
			tag += 2;
		}
		i++;
	}
	shape->letter = 'A' + count;
}

int check_tetramino2(char *str, int ret, int i)
{
	int		tag;

	tag = 0;
	if (i % 5 < 4)
	{
		if (!(str[i] == '.' || str[i] == '#'))
			return (0);
		if (str[i] == '#' && ++tag > 4)
			return (0);
	}
	else if (str[i] != '\n')
		return (0);
	if (ret == 21 && str[20] != '\n')
		return (0);
	return (1);
}

int 	check_tetramino(char *str, int ret)
{
	int		i;
	int 	cnt_border;
	int 	cnt_cell;

	i = 0;
	cnt_border = 0;
	cnt_cell = 0;
	while(i < 20) {
		if (str[i] == '#') {
			if ((i - 1) >= 0 && str[i - 1] == '#')
				cnt_border++;
			if ((i + 1) < 20 && str[i + 1] == '#')
				cnt_border++;
			if ((i - 5) >= 0 && str[i - 5] == '#')
				cnt_border++;
			if ((i + 5) < 20 && str[i + 5] == '#')
				cnt_border++;
			cnt_cell++;
		}
		if (!check_tetramino2(str, ret, i))
			return (0);
		i++;
	}
	return ((cnt_border == 6 || cnt_border == 8) && cnt_cell == 4);
}

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
		save_coord(buf, *shape, count);
		move_shape(*shape);
		(*shape)->next = creat_new_list();
		*shape = (*shape)->next;
	}
	return (1);
}

void		parser(char **file, t_shape **shape)
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
			break ;
		}
		count++;
	}
	free(buf);
	close(fd);
}

int     main(int argc, char *argv[])
{
    if (argc == 1)
        return (0);
	t_shape	*shape;
	t_shape	*head;
	shape = creat_new_list();
	head = shape;
	parser(&argv[1], &shape);
	return (0);

}

	// char line[22] = {"....\n....\n....\n....\n\n"};
	// char map[100];
	// ft_bzero(map, 99);
	// int l = 0;
	// int i = 0;
	// while (head->next)
	// {
	// 	l = 0;
	// 	i = 0;
	// 	while (l < 20)
	// 	{
	// 		if (line[l] == '\n')
	// 			l++;
	// 		if (l % 5 == head->coord[i] && l / 5 == head->coord[i+1])
	// 		{
	// 			line[l] = '#';
	// 			i+=2;
	// 		}
	// 		// printf("%d", head->coord[l++]);
	// 		l++;
	// 	}
	// 	printf("%s", line);
	// 	ft_strcpy(line, "....\n....\n....\n....\n\n");
	// 	head = head->next;
	// }

//int 	checker(char **line)
//{
//	int 	num_cell;
//
//	if (ft_strlen(line) != 4)
//		return (0);
//	while(*line)
//	{
//		if (*line != '.' || *line != '#')
//			return (0);
//		else if (*line == '#')
//			num_cell++;
//	}
//}
// void	parser(char **file)
// {
//     int		fd;
//     char    *line;
//     char	**tetramino;
// 	int 	i = 0;
// 	t_shape		*shape;
// 	int		coord[8];

//     tetramino = (char **)malloc(5 * sizeof(char *));
//     fd = open(*file, O_RDONLY);

//     while(get_next_line(fd, &line) > 0)
// 	{
// 		tetramino[i % 5] = line;
// 		if (i == 5)
// 			if (!check_validate(tetramino, shape))
// 			{
// 				printf("error");
// 				printf("%s", *tetramino);
// 				move_shape(shape);
// 				int l = 0;
// 				while (l < 8)
// 				{
// 					printf("%d", shape->coord[l++]);
// 				}
// 				break ;
// 			}
// 		line = NULL;
// 		i++;
// 	}

// 	move_shape(shape);
// 	int x = 0;
// 	while (x <= 8)
// 		printf("%d\n", coord[x++]);
// 	// printf("%s\n", tetramino[1]);
// 	// printf("%s\n", tetramino[2]);
//     // printf("%s\n", tetramino[3]);
//     free(tetramino);
//     close(fd);
// }
