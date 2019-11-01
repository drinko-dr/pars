/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flag_f.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/30 19:21:46 by drinko            #+#    #+#             */
/*   Updated: 2019/11/01 15:19:08 by marvin           ###   ########.fr       */
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
		len = print_flag_f((long double)va_arg(*ap, double),
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

void	check_num(intmax_t befor, double *num)
{
	if (*num < 0)
	{
		*num *= -1;
		*num = *num - (befor * -1);
	}
	else
		*num = *num - befor;
}
void	calc_point(t_flag **flag)
{
	if ((*flag)->point == -1)
		(*flag)->point = 1000000;
	else
		(*flag)->point = pow_ten((*flag)->point);
}
int		print_flag_f(double num, t_flag **flag)
{
	int		count;
	int		count2;
	intmax_t		temp_bef;
	uintmax_t		temp_aft;
	char	*mass;

	count = 0;
	calc_point(flag);
	count = num_count(num);
	if (num == 0)
	{
		count = 1;
		num += 1;
	}
	temp_bef = num;
	check_num(temp_bef, &num);
	temp_aft = num * (*flag)->point;
	count2 = count + num_count(temp_aft);
	mass = save_digit(&temp_bef, &temp_aft, count, count2);
	if (mass != NULL)
		(*flag)->width -= (count2 = ft_strlen(mass));
	print_str_position(mass, *flag);
	return (len_digit_f((*flag), count2));
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
char	*create_mass(intmax_t *befor, int *count, int *count2, int *temp)
{	char	*mass;

	mass = NULL;
	if (!(mass = (char*)malloc(sizeof(char) * ((*count) + (*count2) + 2))))
		return (NULL);
	if (*befor < 0)
	{
		*befor *= -1;
		*count2 += 1;
		*count += 1;
		mass[0] = '-';
	}
	*temp = *count;
	mass[*count] = '.';
	mass[*count2 + 1] = '\0';
	return (mass);
}

char	*save_digit(intmax_t *befor, uintmax_t *after, int count, int count2)
{
	char	*mass;
	int		temp;

	temp = 0;
	if (!(mass = create_mass(befor, &count, &count2, &temp)))
		return (NULL);
	while (count - 1 >= 0 && *befor != 0)
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
