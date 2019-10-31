/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flag_f.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drinko <drinko@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/30 19:21:46 by drinko            #+#    #+#             */
/*   Updated: 2019/10/31 23:20:49 by drinko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
int		f_flag(va_list *ap, t_flag **flag, char **str)
{
	int		len;
	int		n;

	len = 0;
	n = 0;
	if ((**str == 'f') && (n += 1))
		len = print_flag_f((long double)va_arg(*ap, double), flag);
	else if ((!ft_strncmp(*str, "lf", 1)) && (n += 2))
		len = print_flag_f((long double)va_arg(*ap, double),
		flag);
	else if ((!ft_strncmp(*str, "Lf", 1)) && (n += 2))
		len = print_flag_f((long double)va_arg(*ap, long double),
		flag);
	else
		return (0);
	move_flag(str, n);
	return (len);
}

int		len_digit_f(t_flag *flag, int count)
{
	if (flag->width > 0)
		count += flag->width;
	if (flag->plus != '\0')
		count++;
	return (count);
}

// void	check_num(intmax_t *befor, uintmax_t *after, int count, int count2)
// {
// 	if (*num < 0)
// 	{
// 		(*num) *= -1;
// 		(*count2) += 1;
// 	}
// }

int		print_flag_f(double num, t_flag **flag)
{
	int		count;
	int		count2;
	intmax_t		temp_bef;
	uintmax_t		temp_aft;
	char	*mass;

	count = 0;
	if ((*flag)->point == -1)
		(*flag)->point = 1000000;
	else
		(*flag)->point = pow_ten((*flag)->point);
	count = num_count(num);
	if (num == 0)
	{
		count = 1;
		num += 1;
	}
	temp_bef = num;
	if (num < 0)
		num *= -1;
	temp_aft = num * (*flag)->point;
	count2 = num_count(temp_aft);
	mass = save_digit(&temp_bef, &temp_aft, count, count2);
	if (mass != NULL)
		(*flag)->width -= (count2 + 1);
	print_str_position(mass, *flag);
	return (len_digit_f((*flag), (count2 + 1)));
}

int			print_str_position(char *mass, t_flag *flag)
{
	int		len;
	int		x;

	len = 0;
	x = flag->width;
	if ((flag->position != '\0'))
	{
		ft_putstr(mass);
		while (x-- > 0)
			write(1, &flag->kind_width, 1);
	}
	else
	{
		while (x-- > 0)
			write(1, &flag->kind_width, 1);
		ft_putstr(mass);
	}
	return (len);
}

void ft_putstr(char *str)
{
	while(*str != '\0')
		write(1, str++, 1);
}

uintmax_t pow_ten(int n)
{
	uintmax_t		num;

	num = 1;
	while (n-- > 0)
		num *= 10;
	return (num);
}

char	*save_digit(intmax_t *befor, uintmax_t *after, int count, int count2)
{
	char	*mass;
	int		temp;

	mass = NULL;
	temp = count;
	if (!(mass = (char*)malloc(sizeof(char) * ((count) + (count2) + 2))))
		return (0);
	if (*befor < 0)
	{
		*befor *= -1;
		// *after *= -1;
		count2 += 1;
		count += 1;
		mass[0] = '-';	
	}
	mass[count] = '.';
	mass[count2 + 1] = '\0';
	while (count - 1 >= 0)
	{
		mass[count - 1] = (*befor % 10) + '0';
		*befor /= 10;
		(count)--;
	}
	while (count2 > temp)
	{
		mass[count2] = (*after % 10) + '0';
		*after /= 10;
		(count2)--;
	}
	return (mass);
}
