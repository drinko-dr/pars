/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kludge.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drinko <drinko@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/21 23:19:07 by drinko            #+#    #+#             */
/*   Updated: 2019/10/22 21:28:19 by drinko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	kludge_s(t_flag **flag, char *ap, int x, int count)
{
	if ((*flag)->position == '-')
	{
		write(1, ap, count);
		while (x-- > 0)
			write(1, " ", 1);
	}
	else
	{
		while (x-- > 0)
			write(1, &(*flag)->kind_width, 1);
		write(1, ap, count);
	}
}

void	kludge_pp(t_flag **flag, int base, intmax_t num)
{
	if ((*flag)->octothorp == '#' && base == 16 && num != 0)
	{
		(*flag)->width -= 2;
		if ((*flag)->point == -1 && (*flag)->kind_width == '0')
		{
			(*flag)->point = (*flag)->width;
			(*flag)->width = 0;
		}
	}
}
