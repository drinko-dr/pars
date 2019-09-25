/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvania <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/03 18:34:32 by lvania            #+#    #+#             */
/*   Updated: 2019/09/08 14:37:08 by lvania           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t len)
{
	unsigned char	*temp_d;
	unsigned char	*temp_s;

	temp_d = (unsigned char*)dest;
	temp_s = (unsigned char*)src;
	if (temp_d == NULL && temp_s == NULL)
		return (NULL);
	if (temp_s < temp_d)
		while (len--)
			temp_d[len] = temp_s[len];
	else
		while (len--)
			*temp_d++ = *temp_s++;
	return (dest);
}
