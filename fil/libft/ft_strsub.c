/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvania <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/05 17:04:06 by lvania            #+#    #+#             */
/*   Updated: 2019/09/08 21:05:24 by lvania           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	char	*ptr;

	if (len > len + 1)
		return (NULL);
	if (!s)
		return (NULL);
	ptr = (char *)malloc((sizeof(char) * (len + 1)));
	if (!ptr)
		return (NULL);
	ft_strncpy(ptr, (char *)(s + start), len);
	ptr[len] = '\0';
	return (ptr);
}
