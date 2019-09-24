/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvania <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/06 14:11:39 by lvania            #+#    #+#             */
/*   Updated: 2019/09/07 10:40:40 by lvania           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void		del_lst(void *content, size_t content_size)
{
	if (content_size)
		free(content);
}

t_list			*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list *tmp;
	t_list *out;
	t_list *prev;

	if (!lst || !f || !(tmp = f(lst)))
		return (NULL);
	out = tmp;
	lst = lst->next;
	prev = out;
	while (lst)
	{
		if (!(tmp = f(lst)))
		{
			if (out)
				ft_lstdel(&out, del_lst);
			return (NULL);
		}
		if (prev)
		{
			prev->next = tmp;
			prev = prev->next;
		}
		lst = lst->next;
	}
	return (out);
}
