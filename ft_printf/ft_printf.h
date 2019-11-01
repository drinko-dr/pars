/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drinko <drinko@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/29 20:16:42 by drinko            #+#    #+#             */
/*   Updated: 2019/11/02 00:56:21 by drinko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include <stdarg.h>
# include <stdarg.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdint.h>
# include <wchar.h>

typedef struct		s_flag
{
	char			*flag;
	int				width;
	intmax_t		point;
	char			kind_width;
	char			position;
	char			plus;
	char			*argc;
	char			octothorp;
}					t_flag;
int					len_digit(t_flag *flag, int count);
int					len_str(t_flag *flag, int count);
int					print_base(intmax_t num, int base, t_flag *flag);
int					ft_putnbr(intmax_t num, int base, t_flag *flag);
int					print_num(intmax_t num, t_flag *flag,
					int fun(intmax_t, int, t_flag*), int base);
int					print_str(char *str);
int					ft_strncmp(char *str1, char *str2, int n);
int					num_count(intmax_t num);
int					get_digit(char **str);
int					ft_strlen(char *str);
void				point(char **str, t_flag **flag, va_list *ap);
void				octothorp(char **str, t_flag **flag);
void				plus(char **str, t_flag **flag);
void				width(char **str, t_flag **flag, va_list *ap);
char				*ft_strchr(char *str, char c);
int					flag_c(char ap, t_flag **flag);
int					flag_s(char *ap, t_flag **flag);
int					flag_d(intmax_t num, t_flag **flag,
					int fun(intmax_t, int, t_flag*), int base);
int					diu_flags(va_list *ap, t_flag **flag, char **str);
int					oxx_flags(va_list *ap, t_flag **flag, char **str);
int					hh_flags(va_list *ap, t_flag **flag, char **str);
int					easy_flag(va_list *ap, t_flag **flag, char **str);
void				check_flag(char **str, va_list *ap,
					t_flag **flag, int *len);
int					check_zero(int *count, intmax_t num, t_flag **flag);
void				list_start(t_flag **node);
void				calc_position(t_flag **flag, int count,
					int base, intmax_t num);
void				move_flag(char **str, int n);
void				get_flag(char **str, t_flag **flag, va_list *ap);
int					parser(char *str, va_list *ap, t_flag **flag);
int					ft_printf(char *format, ...);
int					print_position(intmax_t num, t_flag **flag,
					int fun(intmax_t, int, t_flag*), int base);
void				kludge_s(t_flag **flag, char *ap, int x, int count);
void				kludge_pp(t_flag **flag, int base, intmax_t num);
void				el(t_flag *flag, int *len, int base);
int					count_ubase(uintmax_t num, int base);
int					flag_u(uintmax_t num, t_flag **flag, int base);
int					num_ucount(uintmax_t num, int base);
int					check_uzero(int *count, uintmax_t num, t_flag **flag);
void				calc_uposition(t_flag **flag, int count, int base);
int					print_uposition(uintmax_t num, t_flag **flag, int base);
void				kludge_upp(t_flag **flag, int base, uintmax_t num);
int					print_ubase(uintmax_t num, int base, t_flag *flag);
int					ft_putunbr(uintmax_t num, int base, t_flag *flag);
int					print_unum(uintmax_t num, t_flag *flag, int base);
int					len_digit_f(t_flag *flag, int count);
void				ft_putstr(char *str);
uintmax_t			pow_ten(int n);
char				*save_digit(intmax_t *befor, uintmax_t *after,
int count, int count2);
void				check_num(intmax_t befor, long double *num);
void				calc_point(t_flag **flag);
char				*create_mass(intmax_t *befor, int *count,
int *count2, int *temp);
int					print_str_position(char *mass, t_flag *flag);
int					print_flag_f(long double num, t_flag **flag);
int					f_flag(va_list *ap, t_flag **flag, char **str);

#endif
