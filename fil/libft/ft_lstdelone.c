/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvania <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/06 13:10:35 by lvania            #+#    #+#             */
/*   Updated: 2019/09/08 20:42:52 by lvania           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdelone(t_list **alst, void (*del)(void *, size_t))
{
	t_list	*list;

	if (!alst || !*alst || !del)
		return ;
	list = *alst;
	del(((*alst)->content), (*alst)->content_size);
	free(*alst);
	*alst = NULL;
}
