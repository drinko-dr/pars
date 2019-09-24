/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvania <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/04 18:41:35 by lvania            #+#    #+#             */
/*   Updated: 2019/09/07 15:29:55 by lvania           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t			ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t		i;
	size_t		j;
	size_t		src_len;

	j = 0;
	i = 0;
	src_len = 0;
	while (dst[i] != '\0' && size > i)
		i++;
	while (src[src_len] != '\0')
		src_len++;
	while (src[j] != '\0' && size > i + j + 1)
	{
		dst[i + j] = src[j];
		j++;
	}
	if (size > i)
		dst[i + j] = '\0';
	return (i + src_len);
}
