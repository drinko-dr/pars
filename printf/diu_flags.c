/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   diu_flags.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drinko <drinko@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/21 19:31:04 by drinko            #+#    #+#             */
/*   Updated: 2019/10/22 23:32:43 by drinko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	u_flag(va_list *ap, t_flag **flag, char **str, int *n)
{
	int		len;

	len = 0;
	*n = 0;
	if ((**str == (*((*flag)->flag = "u\0\0"))) && (*n += 1))
		len = flag_u((unsigned int)va_arg(*ap, unsigned int),
		flag, 10);
	else if (!ft_strncmp(*str, ((*flag)->flag = "lu\0"), 1) && (*n += 2))
		len = flag_u((unsigned long)va_arg(*ap, unsigned long),
		flag, 10);
	else if (!ft_strncmp(*str, ((*flag)->flag = "llu"), 2) && (*n += 3))
		len = flag_u((unsigned long long)va_arg
(*ap, unsigned long long), flag, 10);
	else
		return (0);
	return (len);
}

int			diu_flags(va_list *ap, t_flag **flag, char **str)
{
	int		n;
	int		len;

	n = 0;
	len = 0;
	if ((**str == 'd' || **str == 'i') && (n += 1))
		len = flag_d((int)va_arg(*ap, int), flag, &ft_putnbr, 10);
	else if ((!ft_strncmp(*str, "ld", 1) ||
	!ft_strncmp(*str, "li", 1)) && (n += 2))
		len = flag_d((long)va_arg(*ap, long int), flag, &ft_putnbr, 10);
	else if ((!ft_strncmp(*str, "lld", 2) ||
	!ft_strncmp(*str, "lli", 2)) && (n += 3))
		len = flag_d((long long)va_arg
(*ap, long long int), flag, &ft_putnbr, 10);
	else if ((!(len = u_flag(ap, flag, str, &n))) && n == 0)
		return (0);
	move_flag(str, n);
	return (len);
}
