/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drinko <drinko@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/21 19:34:18 by drinko            #+#    #+#             */
/*   Updated: 2019/10/22 19:55:53 by drinko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		check_zero(int *count, intmax_t num, t_flag **flag)
{
	if (num == 0 && (*flag)->point == 0)
		*count = 0;
	if ((*count != 0 && num == 0 && (*flag)->octothorp == '#') ||
	(num == 0 && (*flag)->octothorp == '#' && (*flag)->flag != NULL &&
	(((*flag)->flag[0] == 'o' || (*flag)->flag[1] == 'o' ||
	(*flag)->flag[2] == 'o'))))
	{
		write(1, "0", 1);
		return (0);
	}
	return (1);
}

void	check_flag(char **str, va_list *ap, t_flag **flag, int *len)
{
	int	l;

	l = 0;
	if ((l = easy_flag(ap, flag, str)))
		*len += l;
	else if ((l = diu_flags(ap, flag, str)))
		*len += l;
	else if ((l = oxx_flags(ap, flag, str)))
		*len += l;
	else if ((l = hh_flags(ap, flag, str)))
		*len += l;
}
