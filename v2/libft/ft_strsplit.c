/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_whitespaces.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvania <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/09 12:08:58 by lvania            #+#    #+#             */
/*   Updated: 2019/09/10 22:25:22 by lvania           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int		num_words(const char *str, char c)
{
	int	words;
	int	i;

	i = 0;
	words = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		if (str[i] == c && str[i + 1] != c)
			words++;
		i++;
	}
	if (str[0] != '\0')
		words++;
	return (words);
}

static	char	*make_word(const char *str, char c, int *i)
{
	char	*s;
	int		j;

	if (!(s = (char *)malloc(sizeof(s) * (ft_strlen(str)))))
		return (NULL);
	j = 0;
	while (str[*i] != c && str[*i])
	{
		s[j] = str[*i];
		j++;
		*i += 1;
	}
	s[j] = '\0';
	while (str[*i] == c && str[*i])
		*i += 1;
	return (s);
}

static void		str_del(char **s)
{
	while (**s)
		free(*s++);
	free(s);
}

char			**ft_strsplit(const char *str, char c)
{
	int		i;
	int		j;
	int		words;
	char	**s;

	i = 0;
	j = 0;
	words = num_words(str, c);
	if (!str || !(s = (char **)malloc(sizeof(s) * (words + 1))))
		return (NULL);
	while (str[i] == c && str[i])
		i++;
	while (j < words && str[i])
	{
		s[j] = make_word(str, c, &i);
		if (!s[j])
		{
			str_del(s);
			return (NULL);
		}
		j++;
	}
	s[j] = NULL;
	return (s);
}
