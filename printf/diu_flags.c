/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   diu_flags.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drinko <drinko@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/21 19:31:04 by drinko            #+#    #+#             */
/*   Updated: 2019/10/21 20:57:31 by drinko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	u_flag(va_list *ap, t_flag **flag, char **str, int *n)
{
	int		len;

	len = 0;
	*n = 0;
	if (**str == (*((*flag)->flag = "u\0\0")))
		len = flag_d((unsigned int)va_arg(*ap, unsigned int),
		flag, &ft_putnbr, 10);
	else if (!ft_strncmp(*str, ((*flag)->flag = "lu\0"),
	(*n = 1)))
		len = flag_d((unsigned long int)va_arg(*ap, unsigned long int),
		flag, &ft_putnbr, 10);
	else if (!ft_strncmp(*str, ((*flag)->flag = "llu"),
	(*n = 2)))
		len = flag_d((unsigned long long int)va_arg
(*ap, unsigned long long int), flag, &ft_putnbr, 10);
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
	if (**str == 'd' || **str == 'i')
		len = flag_d((int)va_arg(*ap, int), flag, &ft_putnbr, 10);
	else if (!ft_strncmp(*str, "ld", (n = 1)) ||
	!ft_strncmp(*str, "li", (n = 1)))
		len = flag_d((long)va_arg(*ap, long int), flag, &ft_putnbr, 10);
	else if (!ft_strncmp(*str, "lld", (n = 2)) ||
	!ft_strncmp(*str, "lli", (n = 2)))
		len = flag_d((long long)va_arg
(*ap, long long int), flag, &ft_putnbr, 10);
	else if (!(len = u_flag(ap, flag, str, &n)))
		return (0);
	move_flag(str, (n += 1));
	return (len);
}
