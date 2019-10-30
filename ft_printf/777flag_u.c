/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   777flag_u.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drinko <drinko@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 20:27:24 by drinko            #+#    #+#             */
/*   Updated: 2019/10/22 21:35:14 by drinko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int			num_ucount(uintmax_t num)
{
	int count;

	count = 0;
	if (num == 0)
		return (1);
	while (num != 0)
	{
		num /= 10;
		count++;
	}
	return (count);
}

int			ft_putunbr(uintmax_t num)
{
	int		n;

	n = 1;
	if (num / 10 > 0)
		n += ft_putunbr(num / 10);
	num %= 10;
	num += '0';
	write(1, &num, 1);
	return (n);
}

int			print_unum(uintmax_t num, t_flag *flag)
{
	int		len;
	int		x;

	len = 0;
	if (num == 0 && flag->point == 0)
		return (0);
	flag->plus = '\0';
	x = flag->point;
	while (x-- > 0)
		write(1, "0", 1);
	len += ft_putunbr(num);
	return (len);
}

int			print_uposition(uintmax_t num, t_flag **flag)
{
	int		len;
	int		x;

	len = 0;
	x = (*flag)->width;
	if (((*flag)->position != '\0'))
	{
		len = print_unum(num, *flag);
		while (x-- > 0)
			write(1, &(*flag)->kind_width, 1);
	}
	else
	{
		while (x-- > 0)
			write(1, &(*flag)->kind_width, 1);
		len = print_unum(num, *flag);
	}
	return (len);
}

int			flag_u(uintmax_t num, t_flag **flag, int base)
{
	int		count;

	count = 0;
	count = num_ucount(num);
	calc_position(flag, count, base, num);
	count = print_uposition(num, flag);
	return (len_digit(*flag, count));
}
