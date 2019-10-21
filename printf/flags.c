/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flags.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drinko <drinko@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/21 19:31:04 by drinko            #+#    #+#             */
/*   Updated: 2019/10/22 00:19:30 by drinko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	hx_flag(va_list *ap, t_flag **flag, char **str, int *n)
{
	int		len;

	len = 0;
	if (!ft_strncmp(*str, "hx", (*n = 1)) ||
	!ft_strncmp(*str, ((*flag)->flag = "hX"),
	(*n = 1)))
		len = flag_d((unsigned short)va_arg(*ap, unsigned int),
		flag, &print_base, 16);
	else if (!ft_strncmp(*str, "hhx", (*n = 2)) ||
	!ft_strncmp(*str, ((*flag)->flag = "hhX"),
	(*n = 2)))
		len = flag_d((unsigned char)va_arg(*ap, unsigned int),
		flag, &print_base, 16);
	else
	{
		*n = 0;
		return (0);
	}
	return (len);
}

static int	hdi_flag(va_list *ap, t_flag **flag, char **str, int *n)
{
	int		len;

	len = 0;
	if (!ft_strncmp(*str, "hd", 1) || !ft_strncmp(*str, "hi", 1))
	{
		len = flag_d((short)va_arg(*ap, int),
		flag, &ft_putnbr, 10);
		*n = 1;
	}
	else if (!ft_strncmp(*str, "hhd", (*n = 2)) ||
	!ft_strncmp(*str, "hhi", (*n = 2)))
		len = flag_d((signed char)va_arg(*ap, int),
		flag, &ft_putnbr, 10);
	else
	{
		*n = 0;
		return (0);
	}
	return (len);
}

int			hh_flags(va_list *ap, t_flag **flag, char **str)
{
	int		n;
	int		len;

	n = 0;
	len = 0;
	if (!ft_strncmp(*str, "ho", 1) && (n += 1))
		len = flag_d((unsigned short)va_arg
(*ap, unsigned int), flag, &print_base, 8);
	else if (!ft_strncmp(*str, "hho", 2) && (n += 2))
		len = flag_d((unsigned char)va_arg
(*ap, unsigned int), flag, &print_base, 8);
	else if (!ft_strncmp(*str, "hu", 1) && (n += 1))
		len = flag_d((unsigned short)va_arg
(*ap, unsigned int), flag, &ft_putnbr, 10);
	else if (!ft_strncmp(*str, "hhu", 2) && (n += 2))
		len = flag_d((unsigned char)va_arg
(*ap, unsigned int), flag, &ft_putnbr, 10);
	else if (n == 0)
		len = hx_flag(ap, flag, str, &n);
	if (n == 0)
		len = hdi_flag(ap, flag, str, &n);
	if (n == 0)
		return (0);
	move_flag(str, (n += 1));
	return (len);
}

int			easy_flag(va_list *ap, t_flag **flag, char **str)
{
	int	len;

	len = 0;
	if (**str == '%')
		len += flag_s("%", flag);
	else if (**str == 's')
		len += flag_s(va_arg(*ap, char*), flag);
	else if (**str == 'c')
		len += flag_c((char)va_arg(*ap, int), flag);
	else if (**str == 'p')
	{
		(*flag)->octothorp = '#';
		(*flag)->flag = "p\0\0";
		len = flag_d((unsigned long long)va_arg
(*ap, unsigned long long int), flag, &print_base, 16);
	}
	else
		return (0);
	move_flag(str, 1);
	return (len);
}
