/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drinko <drinko@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/29 20:16:42 by drinko            #+#    #+#             */
/*   Updated: 2019/10/10 22:27:12 by drinko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include <stdarg.h>
// # include "libft/libft.h"

typedef struct		 s_flag
{
	char			flag[10];
	int				width;
	int				point;
	char 			kind_width;
	char			position;
	char			plus;
	struct s_flag	*next;
}					t_flag;

# endif
