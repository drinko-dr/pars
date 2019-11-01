/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drinko <drinko@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/21 19:23:43 by drinko            #+#    #+#             */
/*   Updated: 2019/11/02 00:38:31 by drinko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	get_flag(char **str, t_flag **flag, va_list *ap)
{
	int		i;
	int		n;

	i = 0;
	n = 0;
	list_start(flag);
	octothorp(str, flag);
	width(str, flag, ap);
	point(str, flag, ap);
	if ((*flag)->octothorp != '#')
		octothorp(str, flag);
	if ((*flag)->width == 0)
		width(str, flag, ap);
	if ((*flag)->point == -1)
		point(str, flag, ap);
}

void	move_flag(char **str, int n)
{
	while (n-- > 0)
		(*str)++;
}

int		parser(char *str, va_list *ap, t_flag **flag)
{
	char	*start;
	int		len;
	int		l;

	len = 0;
	while (*str != '\0')
	{
		start = str;
		l = 0;
		str = ft_strchr(str, '%');
		if (*str != '\0')
			str++;
		get_flag(&str, flag, ap);
		len += print_str(start);
		check_flag(&str, ap, flag, &len);
	}
	return (len);
}

int		ft_printf(char *format, ...)
{
	int		len;
	va_list	ap;
	t_flag	*flag;

	len = 0;
	flag = NULL;
	flag = (t_flag *)malloc(sizeof(t_flag));
	va_start(ap, format);
	len = parser(format, &ap, &flag);
	free(flag);
	va_end(ap);
	return (len);
}
