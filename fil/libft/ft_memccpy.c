/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvania <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/03 16:36:13 by lvania            #+#    #+#             */
/*   Updated: 2019/09/07 17:56:33 by lvania           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dest, const void *src, int c, size_t n)
{
	unsigned char	*temp_d;
	unsigned char	*temp_s;

	temp_d = (unsigned char*)dest;
	temp_s = (unsigned char*)src;
	if (temp_d == NULL && temp_s == NULL)
		temp_d = NULL;
	while (n--)
	{
		if (*temp_s == (unsigned char)c)
		{
			*temp_d = *temp_s;
			return (&(*temp_d) + 1);
		}
		*temp_d++ = *temp_s++;
	}
	return (NULL);
}
