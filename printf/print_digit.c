/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_digit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drinko <drinko@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/21 19:15:51 by drinko            #+#    #+#             */
/*   Updated: 2019/10/21 23:09:24 by drinko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int			print_base(intmax_t num, int base, t_flag *flag)
{
	int		n;
	char	c;

	n = 1;
	c = 'a';
	if (num / base > 0)
		n += print_base(num / base, base, flag);
	if (flag->flag != NULL && (flag->flag[0] == 'X' || flag->flag[1] == 'X' ||
				flag->flag[2] == 'X'))
		c = 'A';
	num = num % base;
	num += (num > 9 ? c - 10 : '0');
	write(1, &num, 1);
	return (n);
}

int			ft_putnbr(intmax_t num, int base, t_flag *flag)
{
	int		n;

	n = 1;
	if (num / 10 > 0)
		n += ft_putnbr(num / 10, base, flag);
	num %= 10;
	num += '0';
	write(1, &num, 1);
	return (n);
}

static void	el(t_flag *flag, int *len, int base)
{
	if (flag->plus == '+' && base == 10)
		write(1, "+", *len += 1);
	else if (flag->octothorp == '#' && base == 8)
		write(1, "0", *len += 1);
	else if (flag->octothorp == '#' && flag->flag != NULL &&
			(flag->flag[0] == 'X' || flag->flag[1] == 'X' ||
			flag->flag[2] == 'X'))
		write(1, "0X", *len += 2);
	else if (flag->octothorp == '#' && base == 16)
		write(1, "0x", *len += 2);
	else if (flag->plus == ' ' && flag->width <= 0)
		write(1, " ", *len += 1);
}

int			print_num(intmax_t num, t_flag *flag,
			int fun(intmax_t, int, t_flag*), int base)
{
	int		len;
	int		x;

	len = 0;
	if (num == 0 && flag->point == 0)
		return (0);
	if (num < 0)
	{
		write(1, "-", len += 1);
		num *= -1;
		flag->plus = '\0';
	}
	el(flag, &len, base);
	flag->plus = '\0';
	x = flag->point;
	while (x-- > 0)
		write(1, "0", 1);
	len += fun(num, base, flag);
	return (len);
}
