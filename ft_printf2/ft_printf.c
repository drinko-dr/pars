#include <stdarg.h>
#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include "ft_printf.h"
#include <unistd.h>

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
		(*str)++;
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

void parser(va_list ap, t_flag *flag)
{
	if (flag->flag[0] == 'd')
	{
		int num = va_arg(ap, int);
		if (flag->width != 0)
		{
			int x = flag->width - num_count(num);
			while (x-- > 0)
				write(1, &flag->kind_width, 1);
		}
		ft_putnbr(num);
	}
	// if (!ft_strncmp(str, "%%", 1))
		// str = persent(str, ap);
	// if (*str == '%' && *(str + 1) >= '0')
		// width(str + 1, ap);
	// if (flag->flag == 'i')
	// if (*str != '\0')
	// 	parser(str, ap);
	// return (1);
}

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
	//   d, i           o, u, x, X
	if (!ft_strncmp(str, "hhd", 2) || !ft_strncmp(str, "hhi", 2)
	|| !ft_strncmp(str, "hho", 2) || !ft_strncmp(str, "hhu", 2)
	|| !ft_strncmp(str, "hhx", 2) || !ft_strncmp(str, "hhX", 2)
	|| !ft_strncmp(str, "lld", 2) || !ft_strncmp(str, "lli", 2)
	|| !ft_strncmp(str, "llo", 2) || !ft_strncmp(str, "llu", 2)
	|| !ft_strncmp(str, "llx", 2) || !ft_strncmp(str, "llX", 2))
		return (3);
	if (!ft_strncmp(str, "hd", 1) || !ft_strncmp(str, "hi", 1)
	|| !ft_strncmp(str, "ho", 1) || !ft_strncmp(str, "hu", 1)
	|| !ft_strncmp(str, "hx", 1) || !ft_strncmp(str, "hX", 1)
	|| !ft_strncmp(str, "ld", 1) || !ft_strncmp(str, "li", 1)
	|| !ft_strncmp(str, "lo", 1) || !ft_strncmp(str, "lu", 1)
	|| !ft_strncmp(str, "lx", 1) || !ft_strncmp(str, "lX", 1))
		return (2);
	if (*str == 'd' || *str == 'i' || *str == 'o' || *str == 'u'
	|| *str == 'x' || *str == 'X')
		return (1);
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

t_flag *get_flag(char **str, t_flag **flag, va_list ap)
{
	t_flag *head;
	int	i;
	int n;

	i = 0;
	n = 0;
	if (!(*flag))
	{
		*flag = create_new_flag();
		head = *flag;
	}
	else
	{
		(*flag)->next = create_new_flag();
		*flag = (*flag)->next;
	}
	width(str, flag, ap);
	//   d, i           o, u, x, X
	if ((n = check_flag(*str)))
	{
		while (n-- > 0)
			(*flag)->flag[i++] = (*(*str++));
		(*flag)->flag[i] = '\0';
	}
	return (head);
}

void parser2(char *str, va_list ap, t_flag **flag)
{
	char *start;

	start = str;
	str = ft_strchr(str, '%');
	str++;
	*flag = get_flag(&str, flag, ap);
	print_str(start);
	parser(ap, *flag);
}
void ft_printf(char *format, ...)
{
	va_list ap;
	t_flag *flag = NULL;
	va_start(ap, format);
	parser2(format, ap, &flag);
	// parser(format, ap);
	va_end(ap);

}

int main ()
{
	int x = 42;
	// ft_printf("some text for test %d one more text befor next %%", x);
	// ft_printf("%10d", 54);
	ft_printf("some text %0*d", 2 ,542222);
	printf("some text %0*d", 2 ,54222);
	// printf("\n", 6, 6, 6, 6);
	return (0);
}