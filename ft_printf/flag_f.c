/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flag_f.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drinko <drinko@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/30 19:21:46 by drinko            #+#    #+#             */
/*   Updated: 2019/10/30 22:47:02 by drinko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
int		f_flag(char **str, va_list *ap, t_flag **flag)
{
	int		len;
	int		n;

	len = 0;
	n = 0;
	if (*str == 'f' && (n += 1))
		len = print_flag((double)va_arg(*ap, double), flag);
	else if ((!ft_strncmp(*str, "lf", 1)) && (n += 2))
		len = print_flag_f((signed char)va_arg(*ap, int),
		flag);
	else if ((!ft_strncmp(*str, "Lf", 1)) && (n += 2))
		len = print_flag_f((long double)va_arg(*ap, long double),
		flag);
	else
		return (0);
	move_flag(str, n);
	return (len);
}

int		print_flag_f(long double num, t_flag **flag)
{
	int		count;
	int		len;
	int		count2;
	int		temp_bef;
	int		temp_aft;
	char	*mass;

	count = 0;
	count = num_count(num);
	temp_bef = num;
	if (num == 0)
	{
		count = 1;
		num += 1;
	}
	temp_aft = num * (*flag)->point * pow_ten(count);
	count2 = num_count(temp_aft) - count;
	mass = save_digit(temp_bef, temp_aft, count, count2);
	if (mass != NULL)
		calc_position(flag, count2 + 1, 10, num);
	len = print_str_position()

}

int			print_str_position(char *mass, t_flag **flag)
{
	int		len;
	int		x;

	len = 0;
	x = (*flag)->width;
	if (((*flag)->position != '\0'))
	{
		len = ft_putstr(mass);
		while (x-- > 0)
			write(1, &(*flag)->kind_width, 1);
	}
	else
	{
		while (x-- > 0)
			write(1, &(*flag)->kind_width, 1);
		len = ft_putstr(mass);
	}
	return (len);
}

void ft_putstr(char *str)
{
	while(*str != '\0')
		write(1, )
}

int pow_ten(int n)
{
	int		num;

	num = 1;
	while (n-- > 0)
		num *= 10;
	return (num);
}

char	*save_digit(int befor, int after, int count, int count2)
{
	char	*mass;

	mass = NULL;
	if (!(mass = (char*)malloc(sizeof(char) * (count + count2 + 2))))
		return (0);
	mass[count] = '.';
	mass[count2 + 1] = '\0';
	while (count - 1 >= 0)
	{
		mass[count - 1] = (befor % 10) + '0';
		befor /= 10;
		count--;
	}
	count2 -= count;
	while (count2 - 1 >= 0)
	{
		mass[count2] = (after % 10) + '0';
		befor /= 10;
		count--;
	}
	return (mass);
}