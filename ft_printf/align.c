/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   align.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drinko <drinko@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/21 19:22:32 by drinko            #+#    #+#             */
/*   Updated: 2019/11/02 00:48:36 by drinko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void		point(char **str, t_flag **flag, va_list *ap)
{
	if (**str == ' ')
	{
		if ((*flag)->plus != '+')
			(*flag)->plus = ' ';
		while (**str == ' ')
			(*str)++;
	}
	if (**str == '.')
	{
		(*str)++;
		if (**str == '*')
		{
			(*flag)->point = va_arg(*ap, int);
			(*str)++;
		}
		else
			(*flag)->point = get_digit(str);
	}
}

void		octothorp(char **str, t_flag **flag)
{
	if (**str == '#')
	{
		(*flag)->octothorp = '#';
		(*str)++;
	}
	if (**str == '+')
	{
		(*flag)->plus = '+';
		while (**str == '+')
			(*str)++;
	}
}

void		plus(char **str, t_flag **flag)
{
	if (**str == '+')
	{
		(*flag)->plus = '+';
		while (**str == '+')
			(*str)++;
	}
}

static void	star(char **str, t_flag **flag, va_list *ap)
{
	if (**str == '*')
	{
		(*flag)->width = va_arg(*ap, int);
		if ((*flag)->width < 0)
		{
			(*flag)->position = '-';
			(*flag)->width *= -1;
		}
		(*str)++;
	}
}

void		width(char **str, t_flag **flag, va_list *ap)
{
	int		x;

	x = 0;
	if (**str == '0')
	{
		while (**str == '0')
			(*str)++;
		(*flag)->kind_width = '0';
	}
	if (**str == '-')
	{
		(*flag)->position = '-';
		(*str)++;
	}
	star(str, flag, ap);
	(x = get_digit(str)) > 0 ?
	(*flag)->width = x : 0;
}
