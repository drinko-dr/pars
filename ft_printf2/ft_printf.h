/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drinko <drinko@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/29 20:16:42 by drinko            #+#    #+#             */
/*   Updated: 2019/10/19 15:13:35 by drinko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include <stdarg.h>
// # include "libft/libft.h"

typedef struct		 s_flag
{
	char			*flag;
	int				width;
	int				point;
	char 			kind_width;
	char			position;
	char			plus;
	struct s_flag	*next;
	char			*argc;
	char			octothorp;
}					t_flag;

# endif