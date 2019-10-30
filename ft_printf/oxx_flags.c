/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   oxx_flags.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drinko <drinko@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/21 19:31:04 by drinko            #+#    #+#             */
/*   Updated: 2019/10/22 21:57:07 by drinko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	o_flag(va_list *ap, t_flag **flag, char **str, int *n)
{
	int		len;

	len = 0;
	*n = 0;
	if (**str == (*((*flag)->flag = "o\0\0")))
	{
		len = flag_u((unsigned int)va_arg
(*ap, unsigned int), flag, 8);
		*n = 1;
	}
	else if (!ft_strncmp(*str, ((*flag)->flag = "lo\0"), 1)
	&& (*n += 2))
		len = flag_u((unsigned long int)va_arg
(*ap, unsigned long int), flag, 8);
	else if (!ft_strncmp(*str, ((*flag)->flag = "llo"), 2)
	&& (*n += 3))
		len = flag_u((unsigned long long int)va_arg
(*ap, unsigned long long int), flag, 8);
	else
	{
		*n = 0;
		return (0);
	}
	return (len);
}

int			oxx_flags(va_list *ap, t_flag **flag, char **str)
{
	int		n;
	int		len;

	n = 0;
	len = 0;
	if ((**str == (*((*flag)->flag = "x\0\0")) ||
	**str == (*((*flag)->flag = "X\0\0"))) && (++n))
		len = flag_u((unsigned int)va_arg(*ap, unsigned int),
		flag, 16);
	else if ((!ft_strncmp(*str, ((*flag)->flag = "lx\0"), 1)
	|| !ft_strncmp(*str, ((*flag)->flag = "lX\0"), 1)) &&
	(n += 2))
		len = flag_u((unsigned long)va_arg(*ap, unsigned long int),
		flag, 16);
	else if ((!ft_strncmp(*str, ((*flag)->flag = "llx"), 2)
	|| !ft_strncmp(*str, ((*flag)->flag = "llX"), 2)) &&
	(n += 3))
		len = flag_u((unsigned long long)va_arg
(*ap, unsigned long long int), flag, 16);
	else
		len = o_flag(ap, flag, str, &n);
	if (n == 0)
		return (0);
	move_flag(str, (n));
	return (len);
}
