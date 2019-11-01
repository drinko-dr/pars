/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_f.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drinko <drinko@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/02 00:39:24 by drinko            #+#    #+#             */
/*   Updated: 2019/11/02 00:44:45 by drinko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int			len_digit_f(t_flag *flag, int count)
{
	if (flag->width > 0)
		count += flag->width;
	if (flag->plus != '\0')
		count++;
	return (count);
}

void		check_num(intmax_t befor, long double *num)
{
	if (*num < 0)
	{
		*num *= -1;
		*num = *num - (befor * -1);
	}
	else
		*num = *num - befor;
}

void		calc_point(t_flag **flag)
{
	if ((*flag)->point == -1)
		(*flag)->point = 1000000;
	else
		(*flag)->point = pow_ten((*flag)->point);
}

void		ft_putstr(char *str)
{
	while (*str != '\0')
		write(1, str++, 1);
}

uintmax_t	pow_ten(int n)
{
	uintmax_t		num;

	num = 1;
	while (n-- > 0)
		num *= 10;
	return (num);
}
