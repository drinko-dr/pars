/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flags.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drinko <drinko@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/21 19:31:04 by drinko            #+#    #+#             */
/*   Updated: 2019/10/30 20:48:50 by drinko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	hx_flag(va_list *ap, t_flag **flag, char **str, int *n)
{
	int		len;

	len = 0;
	if ((!ft_strncmp(*str, ((*flag)->flag = "hx\0"), 1)
	|| !ft_strncmp(*str, ((*flag)->flag = "hX\0"), 1))
	&& (*n += 2))
		len = flag_u((unsigned short int)va_arg(*ap, unsigned int),
		flag, 16);
	else if ((!ft_strncmp(*str, ((*flag)->flag = "hhx"), 2)
	|| !ft_strncmp(*str, ((*flag)->flag = "hhX"), 2))
	&& (*n += 3))
		len = flag_u((unsigned char)va_arg(*ap, unsigned int),
		flag, 16);
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
		*n = 2;
	}
	else if ((!ft_strncmp(*str, "hhd", 2) ||
	!ft_strncmp(*str, "hhi", 2)) && (*n += 3))
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
	if (!ft_strncmp(*str, "ho", 1) && (n += 2))
		len = flag_u((unsigned short)va_arg
(*ap, unsigned int), flag, 8);
	else if (!ft_strncmp(*str, "hho", 2) && (n += 3))
		len = flag_u((unsigned char)va_arg
(*ap, unsigned int), flag, 8);
	else if (!ft_strncmp(*str, "hu", 1) && (n += 2))
		len = flag_u((unsigned short)va_arg
(*ap, unsigned int), flag, 10);
	else if (!ft_strncmp(*str, "hhu", 2) && (n += 3))
		len = flag_u((unsigned char)va_arg
(*ap, unsigned int), flag, 10);
	else if (n == 0)
		len = hx_flag(ap, flag, str, &n);
	if (n == 0)
		len = hdi_flag(ap, flag, str, &n);
	if (n == 0)
		return (0);
	move_flag(str, n);
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
		(*flag)->width -= 2;
		len = flag_u((unsigned long long)va_arg
(*ap, unsigned long long int), flag, 16);
	}
	else
		return (0);
	move_flag(str, 1);
	return (len);
}
