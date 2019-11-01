/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drinko <drinko@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/21 19:24:16 by drinko            #+#    #+#             */
/*   Updated: 2019/11/02 00:30:21 by drinko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		len_str(t_flag *flag, int count)
{
	int		len;

	len = 0;
	if (flag->width > 0)
		len += flag->width;
	if (flag->point == count)
		len += count;
	else
		len += count;
	return (len);
}

int		len_digit(t_flag *flag, int count)
{
	int	len;

	len = 0;
	if (flag->width > 0)
		len += flag->width;
	if (flag->point > 0)
		len += flag->point;
	len += count;
	return (len);
}

char	*ft_strchr(char *str, char c)
{
	while (*str)
	{
		if (*str == c)
			return (str);
		str++;
	}
	return (str);
}

void	list_start(t_flag **node)
{
	(*node)->flag = NULL;
	(*node)->kind_width = ' ';
	(*node)->point = -1;
	(*node)->width = 0;
	(*node)->position = '\0';
	(*node)->plus = '\0';
	(*node)->octothorp = '\0';
}

void	calc_position(t_flag **flag, int count, int base, intmax_t num)
{
	if ((*flag)->point > 0 || (*flag)->position != '\0')
	{
		(*flag)->kind_width = ' ';
		(*flag)->point - count > 0 ?
			(*flag)->width -= ((*flag)->point - count) : 0;
		(*flag)->point = (*flag)->point - count;
	}
	(*flag)->width -= count;
	if (((num < 0 || (*flag)->plus == '+' || ((*flag)->plus == ' '
	&& (*flag)->point == -1)) && base == 10) ||
			((*flag)->octothorp == '#' && base == 8))
	{
		(*flag)->width -= 1;
		if ((*flag)->point == -1 && (*flag)->kind_width == '0')
		{
			(*flag)->point = (*flag)->width;
			(*flag)->width = 0;
		}
	}
}
