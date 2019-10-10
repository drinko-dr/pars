#include <stdarg.h>
#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include "ft_printf.h"

void ft_putnbr(int num);

void ft_putnbr(int num)
{
	if (num / 10 > 0)
		ft_putnbr(num /10);
	num %= 10;
	num += '0';
	write(1, &num, 1);
}

char *print_str(char *str)
{
	while (*str && *str != '%')
		write(1, str++, 1);
	return (str);
}

char *digit(char *str, va_list ap)
{
	int x = va_arg(ap, int);
	ft_putnbr(x);
	return (str + 2);
}

char *persent(char *str, va_list ap)
{
	write(1, "%%", 1);
	return (str + 2);
}

int ft_strncmp(char *str1, char *str2, int n)
{
	while (*str1 ==*str2 && n-- > 0)
	{
		str1++;
		str2++;
	}
	return (*str1 - *str2);
}

int num_count(int num)
{
	int count = 0;
	while (num > 0)
	{
		num /= 10;
		count++;
	}
	return (count);
}

void width(char **str, t_flag **flag, va_list ap)
{
	int num = 0;
	int point = 0;
	if (**str == '0' && *(*str - 1) == '%')
	{
		while (**str == '0')
			(*str)++;
		(*flag)->kind_width = '0';
	}
	if (**str == '*')
	{
		(*flag)->width = va_arg(ap, int);
		*(str++);
	}
	else
	{
		while (**str >= '0' && **str <= '9')
			num = num * 10 + ((*(*str)++) - '0');
		(*flag)->width = num;
	}
	if (**str == '.')
		width((&*str + 1), flag, ap);
}

// int parser(char *str, va_list ap)
// {
// 	int point = 0;
// 	str = print_str(str);
// 	if (!ft_strncmp(str, "%d", 1))
// 		str = digit(str, ap);
// 	if (!ft_strncmp(str, "%%", 1))
// 		str = persent(str, ap);
// 	if (*str == '%' && *(str + 1) >= '0')
// 		width(str + 1, ap);
// 	if (*str != '\0')
// 		parser(str, ap);
// 	return (1);
// }

char *ft_strchr(char *str, char c)
{
	char *temp;
	temp = str;
	while (*temp)
	{
		if (*temp == c)
			return (temp);
		temp++;
	}
	return (str);
}

int check_flag(char *str)
{
	// hhd hhi hho hhu hhx hhX
	// lld lli llo llu llx llX
	// hd hi ho hu hx hX
	// ld li lo lu lx lX
	// hh, h, l and ll.
	//   d, i           o, u, x, X
	if (!ft_strncmp(str, "hhd", 2) || !ft_strncmp(str, "hhi", 2) || !ft_strncmp(str, "hho", 2)
	|| !ft_strncmp(str, "hhu", 2) || !ft_strncmp(str, "hhx", 2) || !ft_strncmp(str, "hhX", 2)
	|| !ft_strncmp(str, "lld", 2) || !ft_strncmp(str, "lli", 2) || !ft_strncmp(str, "llo", 2)
	|| !ft_strncmp(str, "llu", 2) || !ft_strncmp(str, "llx", 2) || !ft_strncmp(str, "llX", 2))
		return (3);
	if (!ft_strncmp(str, "hd", 2) || !ft_strncmp(str, "hi", 2) || !ft_strncmp(str, "ho", 2)
	|| !ft_strncmp(str, "hu", 2) || !ft_strncmp(str, "hx", 2) || !ft_strncmp(str, "hX", 2)
	|| !ft_strncmp(str, "ld", 2) || !ft_strncmp(str, "li", 2) || !ft_strncmp(str, "lo", 2)
	|| !ft_strncmp(str, "lu", 2) || !ft_strncmp(str, "lx", 2) || !ft_strncmp(str, "lX", 2))
		return (2);
	return (0);
}

t_flag *create_new_flag(void)
{
	t_flag *node;
	node = (t_flag *)malloc(sizeof(t_flag));
	node->kind_width = ' ';
	node->point = 0;
	node->width = 0;
	node->next = NULL;
	return (node);
}

void get_flag(char *str, t_flag **flag, va_list ap)
{
	t_flag *node;
	node = *flag;
	if (!node)
		node = create_new_flag();
	else
	{
		node->next = create_new_flag();
		node = node->next;
	}
	width(&str, &node, ap);
	int i = 0;
	int n = 0;
	//   d, i           o, u, x, X
	if ((n = check_flag(str)))
	{
		while (n-- > 0)
			(*flag)->flag[i++] = *str++;
		(*flag)->flag[i] = *str;
		(*flag)->flag[i] = '\0';
	}
}

void parser2(char *str, va_list ap, t_flag **flag)
{
	str = ft_strchr(str, '%');
	get_flag(str + 1, flag, ap);
}
void ft_printf(char *format, ...)
{
	va_list ap;
	t_flag *flag = NULL;
	va_start(ap, format);
	parser2(format, ap, &flag);
	print_str(format);
	// parser(format, ap);
	va_end(ap);

}

int main ()
{
	int x = 42;
	// ft_printf("some text for test %d one more text befor next %%", x);
	// ft_printf("%10d", 54);
	// ft_printf("some text %010d", 54);
	// printf("some %0.*dkjyt", 42);
	printf("\n", 6, 6, 6, 6);
	return (0);
}