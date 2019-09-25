/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvania <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/05 15:45:44 by lvania            #+#    #+#             */
/*   Updated: 2019/09/08 22:02:36 by lvania           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnew(size_t size)
{
	char	*str;

	if (size > size + 1)
		return (NULL);
	str = (char *)malloc(sizeof(unsigned char) * (1 + size));
	if (!str)
		return (NULL);
	ft_memset(str, '\0', size + 1);
	return (str);
}
