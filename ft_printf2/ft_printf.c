#include <stdarg.h>
#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include "ft_printf.h"
#include <io.h>
#include <stdint.h>

void print_point(t_flag *flag)
{
	while (flag->point-- > 0)
			write (1, "0", 1);
}

//выводит число
void ft_putnbr(intmax_t num, t_flag *flag)
{
	if (num < 0)
	{
		write(1, "-", 1);
		num *= -1;
		flag->plus = '\0';
	}
	else if (flag->plus == '+' && (flag->flag[0] != 'u'
	&& flag->flag[1] != 'u' && flag->flag[2] != 'u'))
	{
		write(1, "+", 1);
		flag->plus = '\0';
	}
	else if (flag->plus == ' ')
		write(1, " ", 1);
	print_point(flag);
	if (num / 10 > 0)
		ft_putnbr(num /10, flag);
	num %= 10;
	num += '0';
	write(1, &num, 1);
}
//выводит строку до знака %
char *print_str(char *str)
{
	while (*str && *str != '%')
		write(1, str++, 1);
	return (str);
}
// хз зачем
char *digit(char *str, va_list ap)
{
	int x = va_arg(ap, int);
	// ft_putnbr(x);
	return (str + 2);
}
//лень на разных компах подключать библиотеки поэтому
//вставлю тут функции (не забыть бы убрать)
int ft_strncmp(char *str1, char *str2, int n)
{
	while (*str1 ==*str2 && n-- > 0)
	{
		str1++;
		str2++;
	}
	return (*str1 - *str2);
}
// счетчик цифр в int
int num_count(intmax_t num)
{
	int count = 0;
	while (num != 0)
	{
		num /= 10;
		count++;
	}
	return (count);
}
//мини atoi
int get_digit(char **str)
{
	int num = 0;
	while (**str >= '0' && **str <= '9')
		num = num * 10 + (*(*str)++ - '0');
	return (num);
}
/*сохранение флага точности, если число не float или double
*то к выводимому числу добавляются 0 с переди
*учитывая флаг ширины
*
*/
void point(char **str, t_flag **flag, va_list *ap)
{
	int num = 0;
	if (**str == ' ')
	{
		(*flag)->plus = ' ';
		while (**str == ' ')
			(*str)++;
	}
	while (**str == ' ')
			(*str)++;
	if (**str == '.')
		(*str)++;
	if (**str == '*')
	{
		(*flag)->point = va_arg(*ap, int);
		(*str)++;
	}
	else
		(*flag)->point = get_digit(str);
}
// сохранение флага ширины и определение чем заполнять ширину 0 или space
void width(char **str, t_flag **flag, va_list *ap)
{
	int num = 0;
	if (**str == '+')
	{
		(*flag)->plus = '+';
		(*str)++;
	}
	if (**str == '0' && *(*str - 1) == '%')
	{
		while (**str == '0')
			(*str)++;
		(*flag)->kind_width = '0';
	}
	if (**str == '-')
	{
		(*flag)->position = '-';
		(*str)++;
	}
	if (**str == '*')
	{
		(*flag)->width = va_arg(*ap, int);
		(*str)++;
	}
	else
		(*flag)->width = get_digit(str);
}

int ft_strlen(char *str)
{
	int count = 0;
	while (str[count])
		count++;
	return (count);
}

int flag_s(va_list *ap, t_flag **flag)
{
	char *str = va_arg(*ap, char*);
	int count = ft_strlen(str);
	if ((*flag)->point != 0)
	{
		(*flag)->point - count > 0 ? 0 : (count = (*flag)->point);
	}
	int x = (*flag)->width - count;
	if ((*flag)->position == '-')
	{
		write(1, str, count);
		while (x-- > 0)
			write(1, " ", 1);
	}
	else
	{
		while (x-- > 0)
			write(1, &(*flag)->kind_width, 1);
		write(1, str, count);
	}
	return (1);
}

//вывод флага d
/* для остальных флагов нужны почти теже действия
* меняется только тип данных для счетчика и выводимого значения
* хотелось бы передовать адрес функции в функцию в зависимости от
* флагов, если это имеет смысл
*/
// int flag_d(va_list *ap, t_flag **flag)

int flag_d(intmax_t num, t_flag **flag)
{
	// int num = va_arg(*ap, int);
	int count = num_count(num);
	if ((*flag)->point != 0 || (*flag)->position != '\0')
	{
		(*flag)->kind_width = ' ';
		(*flag)->point - count > 0 ? (*flag)->width -= ((*flag)->point - count) : 0;
		(*flag)->point = (*flag)->point - count;
	}
	if (num < 0)
		(*flag)->width -= 1;
	int x = (*flag)->width - count;
	if (((*flag)->position != '\0'))
	{
		ft_putnbr(num, *flag);
		while (x-- > 0)
			write(1, &(*flag)->kind_width, 1);
	}
	else
	{
		while (x-- > 0)
			write(1, &(*flag)->kind_width, 1);
		ft_putnbr(num, *flag);
	}
	return (1);
}
//еще одна
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
//проверка на валидный флаг, возвращает 0 если такого флага нет
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
	|| *str == 'x' || *str == 'X' || *str == '%' || *str == 's')
		return (1);
	return (0);
}
// возможно мне не нужен односвязный список, достаточно каждый раз обнулять одну структуру
//
void list_start(t_flag **node)
{
	(*node)->flag[0] = '\0';
	(*node)->flag[1] = '\0';
	(*node)->flag[2] = '\0';
	(*node)->kind_width = ' ';
	(*node)->point = 0;
	(*node)->width = 0;
	(*node)->next = NULL;
	(*node)->position = '\0';
	(*node)->plus = '\0';
	// (*node)->argc = (char *)malloc(sizeof(char) * (num_count));
}
//ищет ширину, точность, и валидный флаг
/*если будет медленно работать с большими числами
* стоит сначало как то обработать валидный флаг, а потом уже
* искать ширину и точность
*/
void *get_flag(char **str, t_flag **flag, va_list *ap)
{
	int	i;
	int n;

	i = 0;
	n = 0;
	list_start(flag);
	width(str, flag, ap);
	point(str, flag, ap);
	//   d, i           o, u, x, X
	if ((n = check_flag(*str)))
		while (n-- > 0)
			(*flag)->flag[i++] = (*((*str)++));
}

int diu_flags(va_list *ap, t_flag **flag)
{
	if ((*flag)->flag[0] == 'd' || (*flag)->flag[0] == 'i')
		flag_d((int)va_arg(*ap, int), flag);
	else if ((*flag)->flag[0] == 'u')
		flag_d((unsigned int)va_arg(*ap, unsigned int), flag);
	else if (!ft_strncmp((*flag)->flag, "ld", 1) || !ft_strncmp((*flag)->flag, "li", 1))
		flag_d((long)va_arg(*ap, long int), flag);
	else if (!ft_strncmp((*flag)->flag, "lu", 1))
		flag_d((unsigned long int)va_arg(*ap, unsigned long int), flag);
	else if (!ft_strncmp((*flag)->flag, "llu", 2))
		flag_d((unsigned long long int)va_arg(*ap, unsigned long long int), flag);
	else if (!ft_strncmp((*flag)->flag, "lld", 2) || !ft_strncmp((*flag)->flag, "lli", 2))
		flag_d((long long)va_arg(*ap, long long int), flag);
}

int oxX_flags(va_list *ap, t_flag **flag)
{
	if ((*flag)->flag[0] == 'o')
		flag_d((int)va_arg(*ap, int), flag);
	else if ((*flag)->flag[0] == 'x' || (*flag)->flag[0] == 'X')
		flag_d((int)va_arg(*ap, int), flag);
	else if (!ft_strncmp((*flag)->flag, "lo", 1))
		flag_d((long int)va_arg(*ap, long int), flag);
	else if (!ft_strncmp((*flag)->flag, "llo", 2))
		flag_d((long long int)va_arg(*ap, long long int), flag);
	else if (!ft_strncmp((*flag)->flag, "lx", 1) || !ft_strncmp((*flag)->flag, "lX", 1))
		flag_d((long)va_arg(*ap, long int), flag);
	else if (!ft_strncmp((*flag)->flag, "llx", 2) || !ft_strncmp((*flag)->flag, "llX", 2))
		flag_d((long)va_arg(*ap, long int), flag);
}

int easy_flag(va_list *ap, t_flag **flag)
{
	if ((*flag)->flag[0] == '%')
		write(1, "%%", 1);
	else if ((*flag)->flag[0] == 's')
		flag_s(ap, flag);
	else
		return (0);
	return (1);
}

//пока не решил как будет называться
//вывод след строки и флага будет идти через цикл скорее всего
int parser(char *str, va_list *ap, t_flag **flag)
{
	char *start;

	while (*str != '\0')
	{
	start = str;
	str = ft_strchr(str, '%');
	str++;
	get_flag(&str, flag, ap);
	print_str(start);
	if (easy_flag(ap, flag))
		continue;
		// return (1);
	else if (diu_flags(ap, flag))
		continue;
	else if (oxX_flags(ap, flag))
		continue;
		// return (1);
	str++;
	}
	return (0);
}
//тупо набор функций
void ft_printf(char *format, ...)
{
	va_list ap;
	t_flag *flag = NULL;
	flag = (t_flag *)malloc(sizeof(t_flag));
	va_start(ap, format);
	parser(format, &ap, &flag);
	// parser(format, ap);
	va_end(ap);
}

int main ()
{
	int x = 42;
	// ft_printf("some text for test %d one more text befor next %%", x);
	// ft_printf("%10d", 54);
	printf("%%lld = %+.14llu\n", 235);
	ft_printf("%%lld = %+.14llu", 235);
	// ft_printf("some text %0-010.1s", "one");
	// ft_printf("some text %*d", 20, 42);

	// printf("\n", 6, 6, 6, 6);
	return (0);
}
