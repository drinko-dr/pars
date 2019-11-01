/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drinko <drinko@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/21 19:27:13 by drinko            #+#    #+#             */
/*   Updated: 2019/11/02 00:50:59 by drinko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int			flag_c(char ap, t_flag **flag)
{
	int		count;
	int		x;

	count = 1;
	if ((*flag)->point != -1 && ap != 0)
	{
		(*flag)->point - count > 0 ? 0 : (count = (*flag)->point);
	}
	(*flag)->width -= count;
	x = (*flag)->width;
	if ((*flag)->position == '-')
	{
		write(1, &ap, 1);
		while (x-- > 0)
			write(1, " ", 1);
	}
	else
	{
		while (x-- > 0)
			write(1, &(*flag)->kind_width, 1);
		write(1, &ap, count);
	}
	return (len_str(*flag, count));
}

int			flag_s(char *ap, t_flag **flag)
{
	int		count;
	int		x;

	count = 0;
	if (ap != NULL)
		count = ft_strlen(ap);
	else
		write(1, "(null)", (count = 6));
	if ((*flag)->point > -1)
	{
		(*flag)->point - count > 0 ? 0 : (count = (*flag)->point);
	}
	(*flag)->width -= count;
	x = (*flag)->width;
	if (ap != NULL && *ap == '%')
		count = 1;
	kludge_s(flag, ap, x, count);
	return (len_str(*flag, count));
}

int			flag_d(intmax_t num, t_flag **flag,
		int fun(intmax_t, int, t_flag*), int base)
{
	int		count;

	count = 0;
	if (num == -9223372036854775807 - 1)
	{
		write(1, "-9223372036854775808", 20);
		return (20);
	}
	count = num_count(num);
	if (check_zero(&count, num, flag) == 0)
		return (1);
	calc_position(flag, count, base, num);
	count = print_position(num, flag, fun, base);
	return (len_digit(*flag, count));
}

int			print_position(intmax_t num, t_flag **flag,
		int fun(intmax_t, int, t_flag*), int base)
{
	int		len;
	int		x;

	len = 0;
	kludge_pp(flag, base, num);
	x = (*flag)->width;
	if (((*flag)->position != '\0'))
	{
		len = print_num(num, *flag, fun, base);
		while (x-- > 0)
			write(1, &(*flag)->kind_width, 1);
	}
	else
	{
		while (x-- > 0)
			write(1, &(*flag)->kind_width, 1);
		len = print_num(num, *flag, fun, base);
	}
	return (len);
}
