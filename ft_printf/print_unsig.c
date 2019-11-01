/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_unsig.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drinko <drinko@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 21:50:37 by drinko            #+#    #+#             */
/*   Updated: 2019/11/02 00:54:08 by drinko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int			print_uposition(uintmax_t num, t_flag **flag, int base)
{
	int		len;
	int		x;

	len = 0;
	kludge_upp(flag, base, num);
	x = (*flag)->width;
	if (((*flag)->position != '\0'))
	{
		len = print_unum(num, *flag, base);
		while (x-- > 0)
			write(1, &(*flag)->kind_width, 1);
	}
	else
	{
		while (x-- > 0)
			write(1, &(*flag)->kind_width, 1);
		len = print_unum(num, *flag, base);
	}
	return (len);
}

int			print_ubase(uintmax_t num, int base, t_flag *flag)
{
	int		n;
	char	c;

	n = 1;
	c = 'a';
	if (flag->point == 0 && flag->flag != NULL && flag->flag[0] == 'p')
		return (0);
	if (num / base > 0)
		n += print_ubase(num / base, base, flag);
	if (flag->flag != NULL && (flag->flag[0] == 'X' || flag->flag[1] == 'X' ||
				flag->flag[2] == 'X'))
		c = 'A';
	num = num % base;
	num += (num > 9 ? c - 10 : '0');
	write(1, &num, 1);
	return (n);
}

int			print_unum(uintmax_t num, t_flag *flag, int base)
{
	int		len;
	int		x;

	len = 0;
	x = 0;
	if (flag->flag != NULL && flag->flag[0] == 'p')
		x = 1;
	if (x == 0 && num == 0 && flag->point == 0)
		return (0);
	el(flag, &len, base);
	x = flag->point;
	while (x-- > 0)
		write(1, "0", 1);
	len += print_ubase(num, base, flag);
	return (len);
}

int			count_ubase(uintmax_t num, int base)
{
	int		n;

	n = 1;
	if (num / base > 0)
		n += count_ubase(num / base, base);
	return (n);
}
