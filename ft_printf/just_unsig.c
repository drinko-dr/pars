/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   just_unsig.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drinko <drinko@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 21:29:33 by drinko            #+#    #+#             */
/*   Updated: 2019/11/02 00:53:24 by drinko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int			flag_u(uintmax_t num, t_flag **flag, int base)
{
	int		count;

	count = 0;
	(*flag)->plus = '\0';
	count = num_ucount(num, base);
	if (check_uzero(&count, num, flag) == 0)
		return (1);
	calc_uposition(flag, count, base);
	count = print_uposition(num, flag, base);
	return (len_digit(*flag, count));
}

int			num_ucount(uintmax_t num, int base)
{
	int count;

	count = 0;
	if (num == 0)
		return (1);
	if (base == 8 || base == 16)
		return (count_ubase(num, base));
	while (num != 0)
	{
		num /= 10;
		count++;
	}
	return (count);
}

int			check_uzero(int *count, uintmax_t num, t_flag **flag)
{
	if (num == 0 && (*flag)->point == 0)
		*count = 0;
	if ((*flag)->flag != NULL && (*flag)->flag[0] == 'p')
		return (1);
	if ((*count != 0 && num == 0 && (*flag)->octothorp == '#') ||
	(num == 0 && (*flag)->octothorp == '#' && (*flag)->flag != NULL &&
	(((*flag)->flag[0] == 'o' || (*flag)->flag[1] == 'o' ||
	(*flag)->flag[2] == 'o'))))
	{
		write(1, "0", 1);
		return (0);
	}
	return (1);
}

void		calc_uposition(t_flag **flag, int count, int base)
{
	if ((*flag)->point != -1 || (*flag)->position != '\0')
	{
		(*flag)->kind_width = ' ';
		(*flag)->point - count > 0 ?
			(*flag)->width -= ((*flag)->point - count) : 0;
		(*flag)->point = (*flag)->point - count;
	}
	(*flag)->width -= count;
	if (((*flag)->octothorp == '#' && base == 8))
	{
		(*flag)->width -= 1;
		if ((*flag)->point == -1 && (*flag)->kind_width == '0')
		{
			(*flag)->point = (*flag)->width;
			(*flag)->width = 0;
		}
	}
}

void		kludge_upp(t_flag **flag, int base, uintmax_t num)
{
	if ((*flag)->octothorp == '#' && base == 16 && num != 0)
	{
		if ((*flag)->flag != NULL && (*flag)->flag[0] != 'p')
			(*flag)->width -= 2;
		if ((*flag)->point == -1 && (*flag)->kind_width == '0')
		{
			(*flag)->point = (*flag)->width;
			(*flag)->width = 0;
		}
	}
	if ((*flag)->octothorp == '#' && base == 8 && (*flag)->point > 0)
		(*flag)->point--;
}
